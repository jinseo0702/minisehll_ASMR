#include "../../include/minishell.h"

void ft_free(char **tokens) {
    size_t i;
    i = 0;
    if (!tokens)
        return;

    while (tokens[i]) {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

t_option *new_option(char *data) {
    t_option *option;
    option = (t_option *)malloc(sizeof(t_option));
    if (!option)
        return NULL;
    
    option->data = strdup(data);
    option->next = NULL;
    option->type = T_OPTION;
    return option;
}

t_arg *new_arg(char *filename, char *variable, char *arg) {
    t_arg *argument;
    argument = (t_arg *)malloc(sizeof(t_arg));
    if (!argument)
        return NULL;

    argument->filename = filename ? strdup(filename) : NULL;
    argument->variable = variable ? strdup(variable) : NULL;
    argument->arg = arg ? strdup(arg) : NULL;
    argument->option = NULL;

    if (filename)
        argument->type = T_FILENAME;
    else if (variable)
        argument->type = T_VARIABLE;
    else
        argument->type = T_OPTION;

    return argument;
}

t_pipe *new_command() {
    t_pipe *command;
    command = (t_pipe *)malloc(sizeof(t_pipe));
    if (!command)
        return NULL;

    command->type = T_PIPE;
    command->cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!command->cmd) {
        free(command);
        return NULL;
    }

    command->cmd->type = T_REDIRECTION;
    command->cmd->redirections = NULL;
    command->cmd->simple_cmd = NULL;
    command->next = NULL;
    return command;
}

void add_redirection(t_cmd *command, char *redirect, t_arg *arg) {
    t_rdts *new_redirection;
    t_rdts *temp;
    
    new_redirection = (t_rdts *)malloc(sizeof(t_rdts));
    if (!new_redirection)
        return;

    new_redirection->redirect = strdup(redirect);
    new_redirection->arg = arg;
    new_redirection->next = NULL;
    new_redirection->type = T_REDIRECTION;
    new_redirection->arg->type = T_FILENAME;

    if (!command->redirections) {
        command->redirections = new_redirection;
    } else {
        temp = command->redirections;
        while (temp->next)
            temp = temp->next;
        temp->next = new_redirection;
    }
}

void add_simple_command(t_cmd *command, char *basic_command, t_arg *arg) {
    t_s_cmd *new_simple_cmd;
    
    new_simple_cmd = (t_s_cmd *)malloc(sizeof(t_s_cmd));
    if (!new_simple_cmd)
        return;

    new_simple_cmd->basic_command = strdup(basic_command);
    new_simple_cmd->arg = arg;
    new_simple_cmd->type = T_BASIC_COMMAND;

    command->simple_cmd = new_simple_cmd;
}

void add_command(t_pipe **command_list, t_pipe *command) {
    t_pipe *temp;
    
    if (!*command_list) {
        *command_list = command;
    } else {
        temp = *command_list;
        while (temp->next)
            temp = temp->next;
        temp->next = command;
    }
}

void add_option(t_arg *arg, char *data) {
    t_option *new_opt;
    t_option *temp;
    
    new_opt = new_option(data);
    if (!new_opt)
        return;

    if (ft_strncmp(data, "$", 1) == 0) {
        arg->variable = ft_strdup(data);
        arg->type = T_VARIABLE;
    } else if ((data[0] == '\'' && data[ft_strlen(data) - 1] == '\'') ||
               (data[0] == '\"' && data[ft_strlen(data) - 1] == '\"')) {
        arg->arg = ft_strdup(data);
        arg->type = T_OPTION;
    } else {
        if (!arg->option) {
            arg->option = new_opt;
        } else {
            temp = arg->option;
            while (temp->next)
                temp = temp->next;
            temp->next = new_opt;
        }
    }
}

char **split_commands_by_pipe(char *input) {
    char **commands;
    
    commands = ft_split(input, '|');
    if (!commands) {
        printf("Error: Failed to split input by pipes\n");
        return NULL;
    }
    return commands;
}

int check_quotes(char *token) {
    T_QUOTO_FLG double_flg;
    T_QUOTO_FLG single_flg;
    size_t k;

    double_flg = EVEN;
    single_flg = EVEN;
    k = 0;

    for (k = 0; token[k] != '\0'; k++) {
        if (token[k] == '"') {
            double_flg = (double_flg == EVEN) ? ODD : EVEN;
        } else if (token[k] == '\'') {
            single_flg = (single_flg == EVEN) ? ODD : EVEN;
        }
    }

    return (double_flg == ODD || single_flg == ODD);
}

void process_redirection(t_cmd *cmd, char **tokens, size_t *j) {
    char *token;
    char *redirect;
    char *filename;

    token = tokens[*j];
    redirect = NULL;
    filename = NULL;

    if (ft_strncmp(token, ">>", 2) == 0) {
        redirect = strndup(token, 2);
        if (ft_strlen(token) > 2) filename = strdup(token + 2);
    } else if (ft_strncmp(token, "<<", 2) == 0) {
        redirect = strndup(token, 2);
        if (ft_strlen(token) > 2) filename = strdup(token + 2);
    } else if (ft_strncmp(token, ">", 1) == 0) {
        redirect = strndup(token, 1);
        if (ft_strlen(token) > 1) filename = strdup(token + 1);
    } else {
        redirect = strndup(token, 1);
        if (ft_strlen(token) > 1) filename = strdup(token + 1);
    }

    if (!filename && tokens[*j + 1]) {
        filename = strdup(tokens[*j + 1]);
        (*j)++;
    }

    if (filename) {
        t_arg *arg = new_arg(filename, NULL, NULL);
        add_redirection(cmd, redirect, arg);
        free(filename);
        
        if (tokens[*j + 1] && tokens[*j + 1][0] != '|' && tokens[*j + 1][0] != '<' && tokens[*j + 1][0] != '>') {
            add_option(arg, tokens[*j + 1]);
            (*j)++;
        }
    } else {
        printf("Warning: Missing filename after redirection '%s'\n", redirect);
    }

    free(redirect);
}

void process_simple_command(t_cmd *cmd, char *token, size_t j) {
    t_arg *arg;
    arg = NULL;

    if (j == 0) {
        arg = new_arg(NULL, NULL, NULL);
        add_simple_command(cmd, token, arg);
    } else {
        add_option(cmd->simple_cmd->arg, token);
    }
}

void parse_and_store(char *input, t_pipe **command_list) {
    char **commands;
    size_t i;
    t_pipe *command;
    char *normalized_command;
    char **tokens;
    size_t j;

    commands = NULL;
    command = NULL;
    normalized_command = NULL;
    tokens = NULL;

    commands = split_commands_by_pipe(input);
    if (!commands) return;

    i = 0;
    while (commands[i]) {
        command = new_command();
        if (!command) break;

        normalized_command = replace_whitespace(commands[i]);
        tokens = ft_split(normalized_command, ' ');
        free(normalized_command);

        j = 0;
        while (tokens[j]) {
            if (check_quotes(tokens[j])) {
                printf("Error: Mismatched quotes in input\n");
                exit(1);
            }

            if ((ft_strncmp(tokens[j], ">", 1) == 0) ||
                (ft_strncmp(tokens[j], "<", 1) == 0) ||
                (ft_strncmp(tokens[j], ">>", 2) == 0) ||
                (ft_strncmp(tokens[j], "<<", 2) == 0)) {
                process_redirection(command->cmd, tokens, &j);
            } else {
                process_simple_command(command->cmd, tokens[j], j);
            }
            j++;
        }

        command->index = i;
        command->pipe = '|';
        add_command(command_list, command);
        ft_free(tokens);
        i++;
    }
    ft_free(commands);
}

void print_commands(t_pipe *command_list) {
    int cmd_num = 0;
    int pipe_num = 0;

    while (command_list) {
        // 현재 명령어의 정보를 출력
        printf("Command %d (Type: %d):\n", cmd_num++, command_list->type);

        // simple_cmd가 있는 경우 기본 명령어와 옵션 출력
        t_s_cmd *simple_cmd = command_list->cmd->simple_cmd;
        if (simple_cmd) {
            printf("  Basic Command (Type: %d): %s\n", simple_cmd->type, simple_cmd->basic_command);

            if (simple_cmd->arg) {
                printf("    Args (Type: %d):\n", simple_cmd->arg->type);

                // filename 필드 출력
                if (simple_cmd->arg->filename)
                    printf("      Filename: %s\n", simple_cmd->arg->filename);

                // option 리스트 출력
                t_option *opt = simple_cmd->arg->option;
                while (opt) {
                    printf("      Option: %s (Type: %d)\n", opt->data, opt->type);
                    opt = opt->next;
                }

                // variable 필드 출력
                if (simple_cmd->arg->variable)
                    printf("      Variable: %s\n", simple_cmd->arg->variable);

                // argument 필드 출력
                if (simple_cmd->arg->arg)
                    printf("      Arg: %s\n", simple_cmd->arg->arg);
            }
        }

        // 리다이렉션 정보 출력
        t_rdts *redirection = command_list->cmd->redirections;
        if (redirection) {
            printf("  Redirections:\n");
            while (redirection) {
                printf("    Redirect: %s (Type: %d)\n", redirection->redirect, redirection->type);

                if (redirection->arg) {
                    printf("    Args:\n");

                    // filename 필드와 arg의 type 필드 출력
                    if (redirection->arg->filename)
                        printf("      Filename: %s\n", redirection->arg->filename);
                    
                    printf("      Arg Type: %d\n", redirection->arg->type);  // T_FILENAME이 설정된 것을 확인

                    // option 리스트 출력
                    t_option *opt = redirection->arg->option;
                    while (opt) {
                        printf("      Option: %s (Type: %d)\n", opt->data, opt->type);
                        opt = opt->next;
                    }

                    // variable 필드 출력
                    if (redirection->arg->variable)
                        printf("      Variable: %s\n", redirection->arg->variable);

                    // argument 필드 출력
                    if (redirection->arg->arg)
                        printf("      Arg: %s\n", redirection->arg->arg);
                }
                redirection = redirection->next;
            }
        }

        // 다음 명령어가 있을 때만 파이프 연산자 출력
        if (command_list->next && command_list->type == T_PIPE) {
            printf("\nPipe %d:\n", pipe_num++);
            printf("        %c\n", command_list->pipe);
        }

        // 다음 명령어로 이동
        command_list = command_list->next;

        // 명령어 구간 간 줄바꿈 추가
        if (command_list) {
            printf("\n");
        }
    }
}

void free_commands(t_pipe *command_list) {
    while (command_list) {
        t_pipe *temp_pipe = command_list;
        t_cmd *cmd = temp_pipe->cmd;

        if (cmd) {
            t_s_cmd *simple_cmd = cmd->simple_cmd;
            if (simple_cmd) {
                free(simple_cmd->basic_command);

                if (simple_cmd->arg) {
                    if (simple_cmd->arg->filename)
                        free(simple_cmd->arg->filename);
                    if (simple_cmd->arg->variable)
                        free(simple_cmd->arg->variable);
                    if (simple_cmd->arg->arg)
                        free(simple_cmd->arg->arg);

                    t_option *opt = simple_cmd->arg->option;
                    while (opt) {
                        t_option *temp_opt = opt;
                        opt = opt->next;
                        free(temp_opt->data);
                        free(temp_opt);
                    }
                    free(simple_cmd->arg);
                }
                free(simple_cmd);
            }

            t_rdts *redir = cmd->redirections;
            while (redir) {
                t_rdts *temp_redir = redir;
                redir = redir->next;

                free(temp_redir->redirect);
                if (temp_redir->arg) {
                    if (temp_redir->arg->filename)
                        free(temp_redir->arg->filename);
                    if (temp_redir->arg->variable)
                        free(temp_redir->arg->variable);
                    if (temp_redir->arg->arg)
                        free(temp_redir->arg->arg);

                    t_option *opt = temp_redir->arg->option;
                    while (opt) {
                        t_option *temp_opt = opt;
                        opt = opt->next;
                        free(temp_opt->data);
                        free(temp_opt);
                    }
                    free(temp_redir->arg);
                }
                free(temp_redir);
            }
            free(cmd);
        }
        command_list = command_list->next;
        free(temp_pipe);
    }
}

// int main(int argc, char **argv) {
//     if (argc < 2) {
//         printf("Usage: %s \"command\"\n", argv[0]);
//         return 1;
//     }

//     t_pipe *command_list = NULL;
//     parse_and_store(argv[1], &command_list);

//     print_commands(command_list);
//     free_commands(command_list);

//     return 0;
// }

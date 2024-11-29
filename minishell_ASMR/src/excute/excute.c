#include "../../include/minishell.h"

char **merge_env(t_mi *mi)
{
    char **exe_env;
    int idx;
    t_node *current;

    idx = -1;
    exe_env = (char **)malloc(sizeof(char *) * (mi->env->size + 1));
    if (exe_env == NULL)
            exit(1);//할당실패시 어떻게 할지 고민입니다.
    current = mi->env->head;
    while (current)
    {
        exe_env[++idx] = ft_strdup(current->val);
        current = current->next;
    }
    exe_env[mi->env->size] = NULL;
    return (exe_env);
}

char **merge_option(t_mi *mi)//option 리스트로 교체할 예정 입니다.
{
    char **exe_option;
    int idx;
    int size;
    t_pan *current;

    idx = -1;
    size = check_size(mi);
    exe_option = (char **)malloc(sizeof(char *) * (size + 1));
    if (exe_option == NULL)
            exit(1);//할당실패시 어떻게 할지 고민입니다.
    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        // printf("size == %s \n", current->val);
        exe_option[++idx] = ft_strdup(current->val);
        remove_pan(mi->head, current);
        current = mi->head->head;
    }
    if (current && current->type == T_PIPE)
    {
        remove_pan(mi->head, current);
        mi->pcnt--;
    }
    exe_option[size] = NULL;
    return (exe_option);
}

void printf_two(char **str)
{
    int idx = -1;
    while (str[++idx])
        printf("%s \n", str[idx]);
}

void exe_cmd(t_mi *mi)
{
    char **two_env;
    char **two_cmd;
    char *path;
    int flag;

    flag = 0;
    find_redi(mi);
    if (mi->head->size == 0)
        return ;
    two_env = merge_env(mi);
    two_cmd = merge_option(mi);
    path = return_path(mi, &two_cmd[0]);
    if (!ft_strncmp(path, "", 1))
    {
        free_two(two_env);
        free_two(two_cmd);
        free(path);//추후 에러는 상의하자. 
        return ;
    }
    excute_cmd(mi, check_builtins(two_cmd[0]), two_cmd);
    if (check_builtins(two_cmd[0]) == BUILT_NOT)
    {
        if (!real_execute(two_env, two_cmd, path))
        {
            ft_putstr_fd(two_cmd[0], 2);
            ft_putendl_fd(" command not found", 2);
            free_two(two_env);
            free_two(two_cmd);
            free(path);//추후 에러는 상의하자.
            ft_free_pcon(mi->head);
            ft_free_env(mi->env);
            ft_free_env(mi->export);
            // printf("ERORR\n");//에러처리 어케 할래??
            exit(127);//이상한 명령어가 들어오면 종료를 합니다.
        }
    }
    free_two(two_env);
    free_two(two_cmd);
    free(path);//추후 에러는 상의하자.
    if (mi->dup == 1)
    {
        ft_free_pcon(mi->head);
        ft_freenull((&mi->input));
        ft_free_env(mi->env);
        ft_free_env(mi->export);
        if (flag < 0)
            exit(1);
        else
            exit(0);
    }
    
}

char *real_execute(char **env, char **cmd, char *path)
{
    // ft_putstr_fd(ft_itoa(getpid()),2);
    // write(2, "\n", 1);
    if (execve(path, cmd, env) == -1)//두번째 인자랑 세번째 인자는 있다고 가정 합니다.
    {
        //error처리를 해야 합니다/
        return (NULL);
    }
    return (NULL);
}

int check_size(t_mi *mi)
{
    t_pan *current;
    int cnt = 0;

    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        cnt++;
        current = current->next;
    }
    return (cnt);
}

int check_fork(t_mi *mi)
{
    t_pan *current;
    char *path;

    current = mi->head->head;
    while (current)
    {
        if (current->type == T_REDIRECTION)
        {
            current = current->next;
            current = current->next;
        }
        else
        {
            break;
        }
    }
    if (!current)
        return (1);
    if (check_builtins(current->val) == BUILT_NOT)
        return (0);
    return (1);
}

int not_fork(t_mi *mi)
{
    int std_i;
    int std_o;

    std_i = dup(0);
    std_o = dup(1);
    if (std_i == -1 || std_o == -1)//표준 입출력중 하나가 에러가 난다면?
        return (-1);//error 처리를 해야한다.
    exe_cmd(mi);
    if (dup2(std_i, 0) == -1 || dup2(std_o, 1) == -1)
        return (-1);//error 처리를 해야한다.
    close(std_i);
    close(std_o);
    return (1);
}

void proc_fork(t_mi *mi)
{//<file1 cat -e | ls -al | C | D
    // int pid;
    int rf = -1;

    if (mi->pcnt == 0)
    {
        if (check_fork(mi) == 1)
        {
            if (not_fork(mi) == -1)
                printf("error 처리하기\n");
            return ;
        }
    }
    while (rf < mi->pcnt)
    {
        rf++;
        if (mi->pcnt > 0 && rf < mi->pcnt)
        {
            if(pipe(mi->fd) == -1)
                exit(1);//error처리하기.
        }
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        mi->pid = fork();
        if (mi->pid == -1)
            exit(1);//error입니다.
        else if (mi->pid == 0)
        {//MASTER
            if (mi->pcnt > 0)
                check_pipe(mi, rf);
            mi->dup = 1;
            exe_cmd(mi);
            ft_freenull((&mi->input));
            ft_free_env(mi->env);
            ft_free_env(mi->export);
            exit(0);
        }
        else
        {
            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            if (mi->pcnt > 0 && rf < mi->pcnt)
                delete_node(mi);
            check_mpipe(mi, rf);
        }
    }
    int status;
    int signo = 0;
    while (waitpid(-1, &status, 0) > 0)
    {
        if (WIFEXITED(status))
            mi->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
        {
            mi->exit_status = 128 + WTERMSIG(status);
            signo = mi->exit_status - 128;
        }
    }
    if (signo == SIGINT)
        printf("^C\n");
    if (signo == SIGQUIT)
        printf("^Quit (core dumped)\n");
}

void check_mpipe(t_mi *mi, int rf)
{
    if (mi->pcnt > 0 && rf < mi->pcnt)
    {
        if (rf > 0)
            close(mi->temp_fd);
        if((mi->temp_fd = dup(mi->fd[0])) == -1)
            exit(1);//error 처리를 고민해야 합니다.
        close(mi->fd[0]);
        close(mi->fd[1]);
    }
    else if (mi->pcnt > 0 && rf == mi->pcnt)
    {
        close(mi->temp_fd);
        close(mi->fd[0]);
        close(mi->fd[1]);
    }
    return ;
}

void check_pipe(t_mi *mi, int rf)
{
    int err_i = 0;
    int err_o = 0;

    if (rf == 0)//처음일때
        err_o = dup2(mi->fd[1], STDOUT_FILENO);
    else if (rf > 0 && rf < mi->pcnt)
    {
        err_i = dup2(mi->temp_fd, STDIN_FILENO);
        err_o = dup2(mi->fd[1], STDOUT_FILENO);
        close(mi->temp_fd);
    }
    else
    {
        err_i = dup2(mi->temp_fd, STDIN_FILENO);
        close(mi->temp_fd);
    }
    if (err_i == -1 || err_o == -1)
        exit(1);//error처리해야 합니다.
    close(mi->fd[0]);
    close(mi->fd[1]);
}

void delete_node(t_mi *mi)
{
    t_pan *current;

    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        remove_pan(mi->head, current);
        current = mi->head->head;
    }
    if (current->type == T_PIPE)
        remove_pan(mi->head, current);
    return ;
}
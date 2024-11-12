#include "../../include/minishell.h"

void prompt(t_con *env)
{
    char *input;
    t_pipe *cmd_lst;

    cmd_lst = NULL;
    while (1)
    {
        if ((input = readline("~$ ")) != NULL)
        {
			add_history(input);
			rl_redisplay();
            parse_and_store(input, &cmd_lst);
            print_commands(cmd_lst);
            // control_cmd(env, input, input);
        }
        else
        {
            free(input);
            exit (1);//에러처리는 고민해야 하는 부분입니다.
        }
        free_commands(cmd_lst);
        cmd_lst = NULL;
        free(input);
        input = NULL;
    }
}
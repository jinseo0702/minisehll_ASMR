#include "../../include/minishell.h"

void prompt(t_con *env)
{
    char *input;

    while (1)
    {
        if ((input = readline("~$ ")) != NULL)
        {
			add_history(input);
			rl_redisplay();
            control_cmd(env, input, input);
        }
        else
        {
            free(input);
            exit (1);//에러처리는 고민해야 하는 부분입니다.
        }
        free(input);
    }
}
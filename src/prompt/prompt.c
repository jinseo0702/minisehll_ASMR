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
            if (ft_strncmp(input, "exit", 4) == 0)
			{
            //exit부분이 완전한 exit부분인지 확인하는 작업이 필요합니다.
            //builtins 부분에 exit함수가 있기에 아직 임시 작업입니다.
				free(input);
				break;
			}
        }
        else
        {
            free(input);
            exit (1);//에러처리는 고민해야 하는 부분입니다.
        }
        free(input);
    }
}
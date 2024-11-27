#include "../../include/minishell.h"

void prompt(t_mi *mi)
{
    while (1)
    {
        if ((mi->input = readline("~$ ")) != NULL)
        {
			add_history(mi->input);
			rl_redisplay();
            control_cmd(mi);
        }
        else
        {
            ft_freenull(&(mi->input));
            exit (1);//에러처리는 고민해야 하는 부분입니다.
        }
        ft_freenull(&(mi->input));
        ft_free_pcon(mi->head);
		mi->pcnt = 0;
		mi->file = 0;
    }
}
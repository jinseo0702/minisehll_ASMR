/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 05:46:19 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 05:58:43 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	prompt(t_mi *mi)
{
	while (1)
	{
		restore_terminal();
		signal_init();
		mi->input = readline("~$ ");
		if (mi->input != NULL)
		{
			init_terminal();
			add_history(mi->input);
			rl_redisplay();
			control_cmd(mi);
		}
		else
		{
			ft_freenull((&mi->input));
			ft_free_env(mi->env);
			ft_free_env(mi->export);
			exit(0);
		}
		ft_freenull(&(mi->input));
		ft_free_pcon(mi->head);
		mi->pcnt = 0;
		mi->file = 0;
	}
}

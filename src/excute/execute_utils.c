/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:23:59 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 08:52:48 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_pipe(t_mi *mi, int rf)
{
	int	err_i;
	int	err_o;

	err_i = 0;
	err_o = 0;
	if (rf == 0)
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
		exit(1);
	close(mi->fd[0]);
	close(mi->fd[1]);
}

void	delete_node(t_mi *mi)
{
	t_pan	*current;

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

void	free_twice(char *str, char *str2)
{
	ft_freenull(&str);
	ft_freenull(&str2);
}

int	create_pipe(t_mi *mi, int rf)
{
	if (mi->pcnt > 0 && rf < mi->pcnt)
	{
		if (pipe(mi->fd) == -1)
			return (-1);
	}
	return (0);
}

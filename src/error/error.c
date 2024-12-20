/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:12:22 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 08:13:40 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	quotes_syntax_error(void)
{
	ft_putendl_fd("syntax error check quotes again!", 2);
}

void	re_syntax_error(char *s)
{
	ft_putstr_fd("syntax error check redi again!", 2);
	if (*s == '<')
		ft_putendl_fd("<<<", 2);
	else if (*s == '>')
		ft_putendl_fd(">>>", 2);
	else
		ft_putendl_fd("||", 2);
}

void	another_syntax_error(char *str)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putendl_fd(str, 2);
}

int	check_error_case(t_mi *mi)
{
	t_pan	*current;

	current = mi->head->head;
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (current->next == NULL || current->next->type == T_PIPE)
			{
				another_syntax_error(current->val);
				return (-100);
			}
		}
		else if (current->type == T_REDIRECTION)
		{
			if (current->next == NULL || current->next->type != T_ARGV)
			{
				another_syntax_error(current->val);
				return (-100);
			}
		}
		current = current->next;
	}
	return (1);
}

void	execve_e_h(t_mi *mi, char **env, char **cmd, char *path)
{
	ft_putstr_fd(cmd[0], 2);
	free_two(env);
	free_two(cmd);
	ft_freenull(&path);
	ft_free_pcon(mi->head);
	ft_free_env(mi->env);
	ft_free_env(mi->export);
}

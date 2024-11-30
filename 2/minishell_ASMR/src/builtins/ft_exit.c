/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:55:08 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 05:19:59 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_con(t_con *con)
{
	t_node	*temp;
	t_node	*next;

	temp = con->head;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
		con->size--;
	}
	con->head = NULL;
	con->tail = NULL;
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_exit(t_mi *mi)
{
	if (mi->env)
		ft_free_con(mi->env);
	if (mi->export)
		ft_free_con(mi->export);
	if (mi->head)
		ft_free_pcon(mi->head);
}

void	ft_check_exit_error(t_mi *mi, char **two_cmd)
{
	if (!two_cmd || !two_cmd[1])
	{
		printf("exit\n");
		ft_free_exit(mi);
		exit(0);
	}
	if (!is_valid_number(two_cmd[1]))
	{
		printf("exit: %s: numeric argument required\n", two_cmd[1]);
		exit(2);
	}
	if (two_cmd[2])
	{
		printf("exit: too many arguments\n");
		return ;
	}
}

void	ft_exit(t_mi *mi, char **two_cmd)
{
	long long	exit_code;

	ft_check_exit_error(mi, two_cmd);
	exit_code = ft_atoi_longlong(two_cmd[1]);
	if (exit_code > 9223372036854775807)
	{
		printf("exit: %s: numeric argument required\n", two_cmd[1]);
		exit (2);
	}
	ft_free_exit(mi);
	printf("exit\n");
	exit(exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:53:15 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 05:12:33 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_echo_option	check_option(char *op)
{
	if (*op != '-')
		return (E_NON);
	op++;
	while (*op)
	{
		if (*op != 'n')
			return (E_NON);
		op++;
	}
	return (E_OP);
}

int	ft_echo(char **two_cmd)
{
	t_echo_option	option;
	int				idx;
	int				flag;

	idx = 0;
	flag = 0;
	option = E_NON;
	while (two_cmd[++idx])
	{
		if (!flag && check_option(two_cmd[idx]) == E_OP)
			option = E_OP;
		if (check_option(two_cmd[idx]) == E_NON)
			break ;
		flag++;
	}
	while (two_cmd[idx])
	{
		printf ("%s", two_cmd[idx]);
		if (two_cmd[idx + 1] != NULL)
			printf (" ");
		idx++;
	}
	if (option == E_NON)
		printf ("\n");
	return (100);
}

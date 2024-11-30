/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:56:46 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 05:14:48 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd_error_check(char **two, int idx)
{
	if (two[++idx])
	{
		printf("pwd don't need any option \n");
		return (-100);
	}
	return (100);
}

int	ft_pwd(char **two_cmd)
{
	char	buf[4100];
	int		idx;

	idx = 0;
	if (ft_pwd_error_check(two_cmd, idx) == -100)
		return (-100);
	ft_memset(buf, 0, sizeof(buf));
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		if (errno == ENOMEM)
			printf("pwd: Memory allocation failed\n");
		else if (errno == EACCES)
			printf("pwd: Permission denied\n");
		else if (errno == ENAMETOOLONG)
			printf("pwd: Path is too long\n");
		else
			printf("pwd: Error retrieving current directory: %s\n", \
					strerror(errno));
		return (-100);
	}
	else
	{
		printf("%s\n", buf);
	}
	return (100);
}

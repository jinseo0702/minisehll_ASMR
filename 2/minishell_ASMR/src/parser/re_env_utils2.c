/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_env_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:02:29 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 09:02:30 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_len(char *str)
{
	int	idx;

	idx = 1;
	while (str[idx])
	{
		if (is_alnumbar(str[idx]) && !ft_isspace(str[idx]))
			idx++;
		else
			return (idx);
	}
	return (idx);
}

int	check_another3(char *str)
{
	int	idx;

	idx = 1;
	while (str[idx] && !is_env(str[idx]))
		idx++;
	return (idx);
}

char	*change_env(char *str, t_mi *mi)
{
	char	*temp;
	char	*temp2;

	if (is_quotes(*str) == '\'')
		return (ft_strtrim(str, "\'"));
	else
	{
		if (is_quotes(*str) == '\"')
		{
			temp = ft_strtrim(str, "\"");
			temp2 = split_env(temp, mi);
			ft_freenull(&temp);
			return (temp2);
		}
		else
		{
			return (split_env(str, mi));
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:55:44 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 08:11:51 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dont_dup(t_mi *mi, char *val)
{
	if (val == NULL)
		return ;
	remove_node(mi->env, search_node(mi->env, val));
	remove_node(mi->export, search_node(mi->export, val));
}

bool	is_dup(t_mi *mi, char *val)
{
	t_node	*temp;

	temp = search_node(mi->export, val);
	if (temp)
	{
		if (ft_strncmp(temp->val, val, ft_strlen(temp->val)) == '=')
			return (false);
		if (!ft_strncmp(temp->val, val, ft_strlen(val)))
			return (false);
	}
	return (true);
}

bool	exp_grammar(char *val)
{
	int	idx;

	idx = 0;
	if (*val == '\0')
		return (false);
	while (val[idx])
	{
		if (idx == 0 && (ft_isalpha(val[idx]) == 0 && val[idx] != '_'))
			return (false);
		if (ft_isalnum(val[idx]) == 0 && val[idx] != '_')
			return (false);
		idx++;
	}
	return (true);
}

bool	ft_arry_grammar_check(char **arry, int idx)
{
	while (arry[0][idx])
	{
		if (idx == 0 && (ft_isalpha(arry[0][idx]) == 0 && arry[0][idx] != '_'))
		{
			ft_free_two(arry);
			return (false);
		}
		if (ft_isalnum(arry[0][idx]) == 0 && arry[0][idx] != '_')
		{
			ft_free_two(arry);
			return (false);
		}
		idx++;
	}
	ft_free_two(arry);
	return (true);
}

bool	env_grammar(t_mi *mi, char *val)
{
	char	**arry;
	int		idx;

	idx = 0;
	if (ft_strchr(val, '=') != NULL)
	{
		arry = ft_split(val, '=');
		if (arry[0] == NULL)
		{
			ft_free_two(arry);
			return (false);
		}
		dont_dup(mi, arry[0]);
		if (ft_arry_grammar_check(arry, idx) == false)
			return (false);
		else
			return (true);
	}
	return (false);
}

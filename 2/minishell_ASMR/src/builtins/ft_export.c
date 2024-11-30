/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:55:44 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 05:30:53 by hyunahn          ###   ########.fr       */
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

size_t	re_two_size(char **two)
{
	size_t	siz;

	siz = 0;
	while (two[siz])
		siz++;
	return (siz);
}

int	ft_play_export(t_mi *mi, char **two, int idx, int flag)
{
	while (two[++idx])
	{
		if (env_grammar(mi, two[idx]))
		{
			insert_node(mi->env, new_node(ft_strdup(two[idx])), INSERT_TAIL);
			insert_node(mi->export, new_node(ft_strdup(two[idx])), INSERT_TAIL);
		}
		else
		{
			if (exp_grammar(two[idx]))
			{
				if (is_dup(mi, &two[idx][0]))
					insert_node(mi->export, new_node(ft_strdup(two[idx])), \
							INSERT_TAIL);
			}
			else
			{
				flag = -100;
				printf("export: '%s':not a valid identifier\n", two[idx]);
			}
		}
	}
	return (flag);
}

int	ft_export(t_mi *mi, char **two)
{
	t_node	*current;
	int		idx;
	int		flag;

	idx = 0;
	flag = 100;
	if (re_two_size(two) == 1)
	{
		current = mi->export->head;
		while (current)
		{
			printf("declare -x %s\n", current->val);
			current = current->next;
		}
		return (flag);
	}
	flag = ft_play_export(mi, two, idx, flag);
	return (flag);
}

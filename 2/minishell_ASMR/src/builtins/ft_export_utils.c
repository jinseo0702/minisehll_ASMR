/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:10:51 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 08:10:52 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

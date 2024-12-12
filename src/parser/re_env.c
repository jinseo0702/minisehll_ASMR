/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:13:16 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 09:01:56 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_env(t_mi *mi)
{
	t_pan	*current;

	current = mi->head->head;
	while (current)
	{
		if (current->type == T_ARGV)
		{
			replace_env(current, mi);
		}
		current = current->next;
	}
}

int	check_another2(char *str)
{
	int	idx;

	idx = 1;
	while (str[idx] && !is_quotes(str[idx]))
		idx++;
	return (idx);
}

void	replace_env(t_pan *pars, t_mi *mi)
{
	t_pcon	*head;
	int		idx;
	int		end;

	idx = 0;
	head = malloc(sizeof(t_pcon));
	init_pcon_pan(head, NULL, LINKED_PCON);
	while (pars->val[idx])
	{
		end = 0;
		if (is_quotes(pars->val[idx]))
		{
			end = check_quotes(&pars->val[idx]);
			if (end == -1)
				break ;
		}
		else
			end += check_another2(&pars->val[idx]);
		insert_pan(head, new_pan(ft_substr(pars->val, idx, end)));
		idx += end;
	}
	ft_freenull(&(pars->val));
	pars->val = merge_word(mi, head);
	ft_free_pcon(head);
}

char	*merge_word(t_mi *mi, t_pcon *head)
{
	t_pan	*current;
	char	*temp;

	temp = NULL;
	current = head->head;
	while (current)
	{
		temp = ft_strjoin_free(temp, change_env(current->val, mi));
		current = current->next;
	}
	return (temp);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp;

	if (s1 == NULL)
		s1 = ft_strdup("");
	if (s2 == NULL)
		s2 = ft_strdup("");
	temp = ft_strjoin(s1, s2);
	ft_freenull(&s1);
	ft_freenull(&s2);
	return (temp);
}

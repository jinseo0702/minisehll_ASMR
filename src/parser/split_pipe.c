/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 06:30:21 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 09:18:28 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_special(char *s)
{
	if (!ft_strncmp(s, "<<<", 3) || \
			!ft_strncmp(s, ">>>", 3) || !ft_strncmp(s, "||", 2))
	{
		re_syntax_error(s);
		return (-100);
	}
	else if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (2);
	else if (!ft_strncmp(s, "<", 1) || \
			!ft_strncmp(s, ">", 1) || !ft_strncmp(s, "|", 1))
		return (1);
	else
		return (0);
}

int	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (c);
	else
		return (0);
}

int	check_quotes(char *str)
{
	char	q_type;
	int		idx;

	q_type = *str;
	idx = 0;
	while (str[++idx])
	{
		if (str[idx] == q_type)
			return (++idx);
	}
	quotes_syntax_error();
	return (-100);
}

int	check_another(char *str)
{
	int	idx;
	int	flag;

	idx = 0;
	while (str[idx] && !ft_isspace(str[idx]) && !is_special(&str[idx]))
	{
		flag = 0;
		if (is_quotes(str[idx]))
		{
			flag = check_quotes(&str[idx]);
			if (flag < 0)
				return (flag);
			idx += flag;
		}
		else
		{
			idx++;
		}
	}
	return (idx);
}

void	cnt_pipe(t_mi *mi)
{
	t_pan	*current;

	current = mi->head->head;
	while (current)
	{
		if (current->type == T_PIPE)
			mi->pcnt++;
		current = current->next;
	}
}

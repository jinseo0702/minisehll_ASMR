/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:19:36 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 10:45:51 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_input_segment(t_mi *mi, int *idx, int *flag, int *end)
{
	int	middle;

	*flag = 0;
	*end = 0;
	if (is_quotes(mi->input[*idx]))
	{
		*flag = check_quotes(&mi->input[*idx]);
		if (*flag < 0)
			return (*flag);
		*end += *flag;
		middle = *end + *idx;
		*flag = check_another(&mi->input[middle]);
	}
	else if (is_special(&mi->input[*idx]))
		*flag += is_special(&mi->input[*idx]);
	else
		*flag += check_another(&mi->input[*idx]);
	if (*flag < 0)
		return (*flag);
	*end += *flag;
	insert_pan(mi->head, new_pan(ft_substr(mi->input, *idx, *end)));
	return (*flag);
}

int	handle_parsing(t_mi *mi)
{
	int	idx;
	int	flag;
	int	end;

	idx = 0;
	flag = 0;
	end = 0;
	while (mi->input[idx])
	{
		if (ft_isspace(mi->input[idx]))
		{
			idx++;
			continue ;
		}
		flag = process_input_segment(mi, &idx, &flag, &end);
		if (flag < 0)
			break ;
		idx += end;
	}
	return (flag);
}

int	pars(t_mi *mi)
{
	int	flag;

	mi->head = malloc(sizeof(t_pcon));
	if (!mi->head)
		exit(1);
	init_pcon_pan(mi->head, NULL, LINKED_PCON);
	flag = handle_parsing(mi);
	cnt_pipe(mi);
	return (flag);
}

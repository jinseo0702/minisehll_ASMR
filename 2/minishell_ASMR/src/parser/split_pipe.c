/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 06:30:21 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 07:05:06 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int process_input_segment(t_mi *mi, int *idx, int *flag, int *end);
static int handle_parsing(t_mi *mi);

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

// int	pars(t_mi *mi)
// {
// 	int	idx;
// 	int	middle;
// 	int	end;
// 	int	flag;

// 	mi->head = malloc(sizeof(t_pcon));
// 	init_pcon_pan(mi->head, NULL, LINKED_PCON);
// 	idx = 0;
// 	while (mi->input[idx])
// 	{
// 		end = 0;
// 		flag = 0;
// 		if (ft_isspace(mi->input[idx]))
// 		{
// 			idx++;
// 			continue ;
// 		}
// 		else if (is_quotes(mi->input[idx]))
// 		{
// 			flag = check_quotes(&mi->input[idx]);
// 			if (flag < 0)
// 				break ;
// 			end += flag;
// 			flag = 0;
// 			middle = end + idx;
// 			flag += check_another(&mi->input[middle]);
// 		}
// 		else if ((flag += is_special(&mi->input[idx])))
// 			;
// 		else
// 		{
// 			flag += check_another(&mi->input[idx]);
// 		}
// 		if (flag < 0)
// 			break;
// 		end += flag;
// 		insert_pan(mi->head, new_pan(ft_substr(mi->input, idx, end)));
// 		idx += end;
// 	}
// 	cnt_pipe(mi);
// 	return (flag);
// }

// 새로운 보조 함수 선언

int pars(t_mi *mi)
{
    mi->head = malloc(sizeof(t_pcon));
    init_pcon_pan(mi->head, NULL, LINKED_PCON);

    int flag = handle_parsing(mi);

    cnt_pipe(mi);
    return (flag);
}

static int handle_parsing(t_mi *mi)
{
    int idx = 0;
    int flag = 0;
    int end = 0;

    while (mi->input[idx])
    {
        if (ft_isspace(mi->input[idx]))
        {
            idx++;
            continue;
        }

        flag = process_input_segment(mi, &idx, &flag, &end);
        if (flag < 0)
            break;

        idx += end;
    }

    return flag;
}

static int process_input_segment(t_mi *mi, int *idx, int *flag, int *end)
{
    *flag = 0;
    *end = 0;

    if (is_quotes(mi->input[*idx]))
    {
        *flag = check_quotes(&mi->input[*idx]);
        if (*flag < 0)
            return *flag;
        *end += *flag;
        int middle = *end + *idx;
        *flag = check_another(&mi->input[middle]);
    }
    else if ((*flag += is_special(&mi->input[*idx])))
		;
    else
    {
        *flag += check_another(&mi->input[*idx]);
    }
    if (*flag < 0)
        return *flag;
    *end += *flag;
    insert_pan(mi->head, new_pan(ft_substr(mi->input, *idx, *end)));
    return *flag;
}
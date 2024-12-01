/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:21:09 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 09:21:33 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_heredoc(t_pcon *head)
{
	t_pan	*current;
	int		pcnt;
	int		tcnt;

	pcnt = 0;
	tcnt = 0;
	current = head->head;
	while (current)
	{
		if (current->type == T_PIPE)
			pcnt++;
		if (current->type == T_REDIRECTION)
		{
			if (!ft_strncmp("<<", current->val, 2))
			{
				tcnt++;
				play_heredoc(current->next, pcnt, tcnt);
			}
		}
		current = current->next;
	}
}

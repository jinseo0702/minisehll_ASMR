/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 06:26:57 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 07:03:13 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	insert_pan(t_pcon *con, t_pan *new)
{
	t_pan	*current;

	if (con->head == NULL)
		con->head = new;
	else
	{
		current = con->head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	con->size++;
}

t_pan	*search_pan(t_pcon *con, char *target)
{
	t_pan	*current;
	int		len;

	len = ft_strlen(target);
	current = con->head;
	while (current)
	{
		if (!ft_strncmp(current->val, target, len))
			return (current);
		current = current->next;
	}
	return (NULL);
}

ssize_t	re_index_pan(t_pcon *con, t_pan *target)
{
	size_t	idx;
	t_pan	*current;

	idx = 0;
	current = con->head;
	while (current)
	{
		if (&*current == &*target)
			return (idx);
		current = current->next;
		idx++;
	}
	return (-1);
}

void	remove_pan(t_pcon *con, t_pan *target)
{
	int		idx;
	int		idx2;
	t_pan	*current;

	idx = re_index_pan(con, target);
	idx2 = 0;
	if (target == NULL)
		return ;
	if (idx == -1)
		return ;
	else if (idx == 0)
		con->head = con->head->next;
	else
	{
		current = con->head;
		while (++idx2 < idx)
			current = current->next;
		current->next = target->next;
	}
	ft_freenull(&(target->val));
	free(target);
	target = NULL;
	con->size--;
}

void	init_pcon_pan(t_pcon *env, t_pan *new, t_clear_type type)
{
	if (type == LINKED_PCON)
	{
		env->head = NULL;
		env->size = 0;
	}
	else if (type == LINKED_PAN)
	{
		new->next = NULL;
		new->val = NULL;
		new->type = T_NULL;
	}
}

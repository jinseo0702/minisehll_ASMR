/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:53:42 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 08:54:07 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	insert_node(t_con *env, t_node *new, t_insert_type type)
{
	if (env->head == NULL)
	{
		env->head = new;
		env->tail = new;
	}
	else if (type == INSERT_TAIL)
	{
		env->tail->next = new;
		new->prev = env->tail;
		env->tail = new;
	}
	else if (type == INSERT_HEAD)
	{
		env->tail->prev = new;
		new->next = env->head;
		env->head = new;
	}
	env->size++;
}

void	remove_node(t_con *env, t_node *target)
{
	if (target == NULL)
		return ;
	if (target->prev)
		target->prev->next = target->next;
	else
	{
		env->head = target->next;
		env->head->prev = NULL;
	}
	if (target->next)
		target->next->prev = target->prev;
	else
	{
		env->tail = target->prev;
		target->next = NULL;
	}
	free(target);
	env->size--;
}

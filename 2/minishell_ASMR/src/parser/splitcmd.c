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

void	ft_free_pcon(t_pcon *env)
{
	t_pan	*temp;
	t_pan	*next;

	temp = env->head;
	while (temp)
	{
		next = temp->next;
		ft_freenull(&(temp->val));
		free(temp);
		temp = next;
		env->size--;
	}
	env->head = NULL;
	free(env);
	env = NULL;
}

t_pan	*new_pan(char *val)
{
	t_pan	*new;

	new = (t_pan *)malloc(sizeof(t_pan));
	if (!new)
	{
		printf("assignment fail!\n");
		exit(1);
	}
	init_pcon_pan(NULL, new, LINKED_PAN);
	new->val = val;
	new->type = check_type(val);
	return (new);
}

t_in_type	check_type(char *val)
{
	if (!ft_strncmp(val, "|", 1) && ft_strlen(val) == 1)
		return (T_PIPE);
	else if (!ft_strncmp(val, ">>", 2) && ft_strlen(val) == 2)
		return (T_REDIRECTION);
	else if (!ft_strncmp(val, "<<", 2) && ft_strlen(val) == 2)
		return (T_REDIRECTION);
	else if (!ft_strncmp(val, "<", 1) && ft_strlen(val) == 1)
		return (T_REDIRECTION);
	else if (!ft_strncmp(val, ">", 1) && ft_strlen(val) == 1)
		return (T_REDIRECTION);
	else
		return (T_ARGV);
}

void	print_pcon(t_pcon *head)
{
	t_pan		*current;
	const char	*type[5];

	type[0] = "T_PIPE";
	type[1] = "T_REDIRECTION";
	type[2] = "T_ARGV";
	type[3] = "T_ENV";
	type[4] = "T_NULL";
	current = head->head;
	while (current)
	{
		printf("val : %s\n", current->val);
		printf("type : %s\n", type[current->type]);
		current = current->next;
	}
}

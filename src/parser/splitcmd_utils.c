/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:05:12 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 09:05:14 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

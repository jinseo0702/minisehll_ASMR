/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:14:34 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 08:16:12 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_redi(t_mi *mi)
{
	t_pan	*current;

	current = mi->head->head;
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_REDIRECTION)
		{
			check_redi(mi, current);
			current = mi->head->head;
			continue ;
		}
		if (current)
			current = current->next;
	}
	return ;
}

int	change_file_fd(t_mi *mi, t_RDT re)
{
	int	fd;

	fd = -100;
	if (re == T_DGREAT || re == T_GREAT)
		fd = dup2(mi->file, STDOUT_FILENO);
	else if (re == T_LESS || re == T_DLESS)
		fd = dup2(mi->file, STDIN_FILENO);
	close(mi->file);
	if (fd == -1)
	{
		if (mi->dup == 1)
			exit(1);
		perror("dup error!!");
	}
	return (fd);
}

void	check_redi(t_mi *mi, t_pan *node)
{
	t_RDT	re;
	t_pan	*temp;

	if (!ft_strncmp(">>", node->val, 2))
		mi->file = open_file(node->next->val, (re = T_DGREAT));
	else if (!ft_strncmp("<<", node->val, 2))
		mi->file = open_file(node->next->val, (re = T_DLESS));
	else if (!ft_strncmp("<", node->val, 1))
		mi->file = open_file(node->next->val, (re = T_LESS));
	else if (!ft_strncmp(">", node->val, 1))
		mi->file = open_file(node->next->val, (re = T_GREAT));
	temp = node->next;
	remove_pan(mi->head, node);
	remove_pan(mi->head, temp);
	if (mi ->file == -1)
	{
		if (mi->dup == 1)
			exit(1);
		mi->of = -1;
		mi->exit_status = 1;
		return ;
	}
	change_file_fd(mi, re);
}

int	open_file(char *file, t_RDT re)
{
	int	fd;

	fd = -100;
	if (re == T_LESS)
		fd = open(file, O_RDONLY, 0644);
	else if (re == T_GREAT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (re == T_DGREAT)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (re == T_DLESS)
	{
		fd = open(file, O_RDONLY, 0644);
		unlink(file);
	}
	if (fd == -1)
		perror(file);
	return (fd);
}

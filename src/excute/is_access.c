/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:26:30 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 08:40:42 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_two(char **two)
{
	int	idx;

	idx = 0;
	while (two[idx])
	{
		ft_freenull(&two[idx]);
		idx++;
	}
	free(two);
}

char	*return_path(t_mi *mi, char **cmd)
{
	char	*path_real;
	char	*path_real2;
	char	**split;
	int		idx;
	t_node	*node;

	idx = -1;
	node = search_node(mi->env, "PATH");
	if (!ft_strncmp(*cmd, "", 1) || node == NULL)
		return (ft_strdup(*cmd));
	split = ft_split(ft_strchr(node->val, '/'), ':');
	while (split[++idx])
	{
		path_real = ft_strjoin(split[idx], "/");
		path_real2 = ft_strjoin(path_real, *cmd);
		if (access(path_real2, F_OK) == 0)
		{
			free_two(split);
			free(path_real);
			return (path_real2);
		}
		free_twice(path_real, path_real2);
	}
	free_two(split);
	return (ft_strdup(*cmd));
}

char	**merge_env(t_mi *mi)
{
	char	**exe_env;
	int		idx;
	t_node	*current;

	idx = -1;
	exe_env = (char **)malloc(sizeof(char *) * (mi->env->size + 1));
	if (exe_env == NULL)
		exit(1);
	current = mi->env->head;
	while (current)
	{
		exe_env[++idx] = ft_strdup(current->val);
		current = current->next;
	}
	exe_env[mi->env->size] = NULL;
	return (exe_env);
}

char	**merge_option(t_mi *mi)
{
	char	**exe_option;
	int		idx;
	int		size;
	t_pan	*current;

	idx = -1;
	size = check_size(mi);
	exe_option = (char **)malloc(sizeof(char *) * (size + 1));
	if (exe_option == NULL)
		exit(1);
	current = mi->head->head;
	while (current && current->type != T_PIPE)
	{
		exe_option[++idx] = ft_strdup(current->val);
		remove_pan(mi->head, current);
		current = mi->head->head;
	}
	if (current && current->type == T_PIPE)
	{
		remove_pan(mi->head, current);
		mi->pcnt--;
	}
	exe_option[size] = NULL;
	return (exe_option);
}

char	*real_execute(char **env, char **cmd, char *path)
{
	if (execve(path, cmd, env) == -1)
	{
		return (NULL);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 01:41:04 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 08:02:04 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_option_cd(char **two_cmd)
{
	int	idx;

	idx = 0;
	while (two_cmd[idx])
		idx++;
	if (idx > 2)
	{
		printf("cd: too many arguments\n");
		return (-100);
	}
	return (100);
}

static char	*check_null_path(char **two_cmd, t_mi *mi)
{
	t_node	*temp;
	char	*path;

	if (!two_cmd[1] || ft_strlen(two_cmd[1]) == 0)
	{
		temp = search_node(mi->env, "HOME");
		if (temp == NULL)
			return (NULL);
		path = ft_strdup(ft_strchr(temp->val, '=') + 1);
	}
	else
	{
		path = ft_strdup(two_cmd[1]);
	}
	if (!path)
	{
		printf("cd: HOME not set\n");
		return (NULL);
	}
	return (path);
}

static char	*check2_null_path(char *path, t_mi *mi)
{
	t_node	*temp;
	char	*home;
	char	*tmp;

	tmp = NULL;
	if (path[0] == '~')
	{
		temp = search_node(mi->env, "HOME");
		if (temp == NULL)
		{
			ft_freenull(&path);
			return (NULL);
		}
		home = ft_strdup(ft_strchr(temp->val, '=') + 1);
		if (path[1] == '/')
			tmp = ft_strjoin(home, &path[1]);
		else if (path[1] == '\0')
			tmp = ft_strdup(home);
		ft_freenull(&home);
		ft_freenull(&path);
		return (tmp);
	}
	tmp = ft_strdup(path);
	ft_freenull(&path);
	return (tmp);
}

static int	move_dir(char *path, char *prev_dir)
{
	if (chdir(path) == -1)
	{
		if (errno == ENOENT)
			printf("cd: %s: No such file or directory\n", path);
		else if (errno == EACCES)
			printf("cd: %s: Permission denied\n", path);
		else if (errno == ENOTDIR)
			printf("cd: %s: Not a directory\n", path);
		else
			printf("cd: %s: Error: %s\n", path, strerror(errno));
		if (chdir(prev_dir) == -1)
			printf ("cd: Failed to return to previous directory: \
					%s\n", strerror(errno));
		ft_freenull(&prev_dir);
		ft_freenull(&path);
		return (-100);
	}
	return (100);
}

int	ft_cd(t_mi *mi, char **two_cmd)
{
	char	*path;
	char	*prev_dir;

	if (check_option_cd(two_cmd) < 0)
		return (-100);
	path = check_null_path(two_cmd, mi);
	if (path == NULL)
		return (-100);
	path = check2_null_path(path, mi);
	if (path == NULL)
		return (-100);
	prev_dir = getcwd(NULL, 0);
	if (!prev_dir)
	{
		printf ("cd: Unable to save current directory\n");
		ft_freenull(&path);
		return (-100);
	}
	if (chdir(path) == -1)
		return (move_dir(path, prev_dir));
	ft_freenull(&prev_dir);
	ft_freenull(&path);
	return (100);
}

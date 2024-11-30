/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 01:41:04 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 02:23:34 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_cd(t_mi *mi, char **two_cmd)
{
	char    *home;
	char *path;
	char *expanded_path;
	char *tmp;
	char    *prev_dir;
	int idx = -1;
	t_node *temp;

	while (two_cmd[++idx])
		;
	if (idx > 2)
	{
		printf("cd: too many arguments\n");
		return (-100);
	}
	if (!two_cmd[1] || ft_strlen(two_cmd[1]) == 0)
	{
		temp = search_node(mi->env, "HOME");
		if (temp == NULL)
			return (-100);
		path = ft_strdup(ft_strchr(temp->val, '=') + 1);
		if (!path)
		{
			printf("cd: HOME not set\n");
			return (-100);
		}
	}
	else
		path = ft_strdup(two_cmd[1]);
	if (path[0] == '~')
	{
		temp = search_node(mi->env, "HOME");
		if (temp == NULL)
		{
			ft_freenull(&path);
			return (-100);
		}
		home = ft_strdup(ft_strchr(temp->val, '=') + 1);
		if (home)
		{
			if (path[1] == '/')
			{
				tmp = ft_strjoin(home, &path[1]);
				ft_freenull(&path);
				path = ft_strdup(tmp);
				ft_freenull(&tmp);
			}
			else if (path[1] == '\0')
			{
				ft_freenull(&path);
				path = ft_strdup(home);
			}
		}
		ft_freenull(&home);
	}
	prev_dir = getcwd(NULL, 0);
	if (!prev_dir)
	{
		printf ("cd: Unable to save current directory\n");
		{
			ft_freenull(&path);
			return (-100);
		}
	}

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
			printf ("cd: Failed to return to previous directory: %s\n", strerror(errno));
		ft_freenull(&prev_dir);
		ft_freenull(&path);
		return (-100);
	}
	ft_freenull(&prev_dir);
	ft_freenull(&path);
	return(100);
}



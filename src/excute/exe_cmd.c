/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 08:24:54 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 08:26:15 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_env_cmd_path(char **env, char **cmd, char *path)
{
	free_two(env);
	free_two(cmd);
	ft_freenull(&path);
}

static void	free_all(t_mi *mi, int flag)
{
	if (mi->dup == 1)
	{
		ft_free_pcon(mi->head);
		ft_freenull((&mi->input));
		ft_free_env(mi->env);
		ft_free_env(mi->export);
		if (flag < 0)
			exit (1);
		else
			exit(0);
	}
}

static void	free_mix(int flag, t_mi *mi)
{
	if (flag < 0 && mi->dup == 0)
		mi->exit_status = 1;
	if (mi->dup == 1)
		free_all(mi, flag);
}

void	exe_cmd(t_mi *mi)
{
	char	**two_env;
	char	**two_cmd;
	char	*path;
	int		flag;

	flag = 0;
	find_redi(mi);
	if (mi->head->size == 0)
		return ;
	two_env = merge_env(mi);
	two_cmd = merge_option(mi);
	path = return_path(mi, &two_cmd[0]);
	if (!ft_strncmp(path, "", 1))
	{
		free_env_cmd_path(two_env, two_env, path);
		return ;
	}
	flag = excute_cmd(mi, check_builtins(two_cmd[0]), two_cmd);
	if (check_builtins(two_cmd[0]) == BUILT_NOT)
		if (!real_execute(two_env, two_cmd, path))
			handle_e_e(mi, two_env, two_cmd, path);
	free_env_cmd_path(two_env, two_cmd, path);
	free_mix(flag, mi);
}

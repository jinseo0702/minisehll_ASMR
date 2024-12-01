/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:02:08 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 09:02:12 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*s_env(char *str, t_mi *mi)
{
	char	*temp;
	t_node	*tmp;

	tmp = search_node(mi->env, &str[1]);
	if (tmp == NULL)
	{
		ft_freenull(&str);
		return (NULL);
	}
	if (ft_strchr(tmp->val, '='))
	{
		temp = ft_strdup(ft_strchr(tmp->val, '=') + 1);
		ft_freenull(&str);
		return (temp);
	}
	ft_freenull(&str);
	return (NULL);
}

char	*process_env_segment(t_mi *mi, char *str, int *end)
{
	char	*temp_env;

	*end = 0;
	if (!ft_strncmp(str, "$?", 2))
	{
		*end = 2;
		temp_env = ft_itoa(mi->exit_status);
	}
	else if (is_env(*str))
	{
		*end = env_len(str);
		if (*end == -1)
			return (NULL);
		if (*end > 1)
			temp_env = s_env(ft_substr(str, 0, *end), mi);
		else
			temp_env = ft_substr(str, 0, *end);
	}
	else
	{
		*end = check_another3(str);
		temp_env = ft_substr(str, 0, *end);
	}
	return (temp_env);
}

char	*split_env(char *str, t_mi *mi)
{
	char	*temp;
	char	*temp_env;
	int		idx;
	int		end;

	temp = NULL;
	idx = 0;
	end = 0;
	while (str[idx])
	{
		temp_env = process_env_segment(mi, &str[idx], &end);
		if (!temp_env)
			break ;
		temp = ft_strjoin_free(temp, temp_env);
		idx += end;
	}
	return (temp);
}

int	is_alnumbar(char c)
{
	int	e;

	e = ft_isalnum(c);
	if (e == 0)
	{
		if (c == '_')
			return (c);
	}
	return (e);
}

int	is_env(char c)
{
	if (c == '$')
		return (c);
	else
		return (0);
}

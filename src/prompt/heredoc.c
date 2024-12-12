/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <hyunahn@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 06:00:20 by hyunahn           #+#    #+#             */
/*   Updated: 2024/12/01 06:13:56 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	play_heredoc(t_pan *current, int pcnt, int tcnt)
{
	char	*limiter;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!current->val)
	{
		printf("heredoc: syntax error near unexpected token `newline'");
		return (1);
	}
	limiter = ft_strdup(current->val);
	if (!limiter)
	{
		printf("heredoc: memory allocation error\n");
		return (1);
	}
	read_get_next(current, limiter, pcnt, tcnt);
	ft_freenull(&limiter);
	return (0);
}

char	*ft_file_name(int pcnt, int tcnt)
{
	char	*temp;
	char	*temp2;
	char	*file_name;
	char	*i_pcnt;
	char	*i_tcnt;

	i_pcnt = ft_itoa(pcnt);
	i_tcnt = ft_itoa(tcnt);
	temp = ft_strjoin(i_pcnt, "_");
	temp2 = ft_strjoin(temp, i_tcnt);
	file_name = ft_strjoin(".temp_", temp2);
	ft_freenull(&i_pcnt);
	ft_freenull(&i_tcnt);
	ft_freenull(&temp);
	ft_freenull(&temp2);
	return (file_name);
}

int	open_temp_file(t_pan *current, int pcnt, int tcnt)
{
	char	*file_name;
	int		file;

	file_name = ft_file_name(pcnt, tcnt);
	file = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0633);
	if (file == -1)
		return (file);
	ft_freenull(&current->val);
	current->val = ft_strdup(file_name);
	ft_freenull(&file_name);
	return (file);
}

void	free_close(char *temp, int file_fd)
{
	ft_freenull(&temp);
	close(file_fd);
}

void	read_get_next(t_pan *current, char *str, int pcnt, int tcnt)
{
	char	*temp;
	int		file_fd;

	file_fd = open_temp_file(current, pcnt, tcnt);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		temp = get_next_line(0);
		if (temp == NULL)
		{
			ft_putstr_fd("delimited by end-of-file (wanted `eof')\n", 2);
			free_close(temp, file_fd);
			return ;
		}
		ft_putstr_fd(temp, file_fd);
		if (!ft_strncmp(temp, str, ft_strlen(str)) \
				&& temp[ft_strlen(str)] == '\n')
		{
			free_close(temp, file_fd);
			return ;
		}
		ft_freenull(&temp);
	}
}

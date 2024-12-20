/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_mi.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:53:00 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 09:58:21 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef STRUCT_MI_H
# define STRUCT_MI_H

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	char			*val;
}	t_node;

typedef struct s_con
{
	struct s_node	*head;
	struct s_node	*tail;
	int				size;
}	t_con;

typedef struct s_mi
{
	char			*input;
	int				file;
	int				pcnt;
	struct s_con	*env;
	struct s_con	*export;
	struct s_pcon	*head;
	int				fd[2];
	int				temp_fd;
	int				exit_status;
	int				dup;
	int				pid;
	int				of;
}	t_mi;

typedef struct s_pan
{
	struct s_pan	*next;
	t_in_type		type;
	char			*val;
}	t_pan;

typedef struct s_pcon
{
	struct s_pan	*head;
	int				size;
}	t_pcon;

#	endif

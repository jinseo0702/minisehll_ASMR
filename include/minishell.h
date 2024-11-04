/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:46:02 by jinseo            #+#    #+#             */
/*   Updated: 2024/08/14 16:47:29 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/gnl_check_bonus/get_next_line.h"
# include "../libft/gnl_check_bonus/get_next_line_bonus.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <errno.h>

//----------------------------------------------
//환경변수 관련
typedef struct s_node
{
    struct s_node *prev;
    struct s_node *next;
    char *val;
} t_node;

typedef struct s_con
{
    struct s_node *head;
    struct s_node *tail;
    int size;
} t_con;

typedef enum e_linked_type
{
    LINKED_CON,
    LINKED_NODE
} t_linked_type;

typedef enum e_insert_type
{
    INSERT_HEAD,
    INSERT_TAIL
} t_insert_type;

//init_env.c
void init_con_node(t_con *env, t_node *new, t_linked_type type);
void ft_free_env(t_con *env);
t_node *new_node(char *val);
void init_env(t_con *env, char **envp);
//ft_env.c
void ft_env(t_con *env);
//control_node.c
void insert_node(t_con *env, t_node *new, t_insert_type type);
void remove_node(t_con *env, t_node *target);
//ft_unset.c
t_node *search_node(t_con *env, char *target);
void ft_unset(t_con *env, char *target);
//ft_export.c
void ft_export(t_con *env, char *val);

//---------------------------------------------

//prompt관련!!!

void prompt(t_con *env);

//---------------------------------------------

//builtins함수들관련 입니다.
typedef enum e_builtins_type
{
    BUILT_ECHO,
    BUILT_CD,
    BUILT_PWD,
    BUILT_EXPORT,
    BUILT_UNSET,
    BUILT_ENV,
    BUILT_EXIT,
    BUILT_NOT
} t_built_type;

t_built_type check_builtins(const char *command);
void excute_cmd(t_con *env, t_built_type cmd, char *input);
void control_cmd(t_con *env, const char *command, char *inptut);
void ft_pwd(void);//ft_pwd.c
//---------------------------------------------
# endif

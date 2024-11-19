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
#include "./enum_mi.h"
#include "./struct_mi.h"
#include "./testparsing.h"
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
void find_redi(t_mi *mi);
int change_file_fd(t_mi *mi, T_RDT re);
void check_redi(t_mi *mi, t_pan *node);
int open_file(char *file, T_RDT re);

//----------------------------------------------

//main
void init_mi(t_mi *mi, char **envp);
//----
//init_env.c
void init_con_node(t_con *env, t_node *new, t_linked_type type);
void ft_free_env(t_con *env);
t_node *new_node(char *val);
// void init_env(t_con *env, char **envp);
t_con *init_env(char **envp);
//ft_env.c
void ft_env(t_mi *mi);//ft_env.c
bool env_grammar(char *val);//ft_env.c
//control_node.c
void insert_node(t_con *env, t_node *new, t_insert_type type);
void remove_node(t_con *env, t_node *target);
//ft_unset.c
t_node *search_node(t_con *env, char *target);
// void ft_unset(t_con *env, char *target);
void ft_unset(t_mi *mi, char **two);
//ft_export.c
// void ft_export(t_con *env, char *val);
void ft_export(t_mi *mi, char **two);
size_t re_two_size(char **two);

//---------------------------------------------

//prompt관련!!!

void prompt(t_mi *mi);

//---------------------------------------------

//builtins함수들관련 입니다.

t_built_type check_builtins(const char *command);
// void excute_cmd(t_con *env, t_built_type cmd, char *input);
void excute_cmd(t_mi *mi, t_built_type cmd, char **two_cmd);
void control_cmd(t_mi *mi);
void ft_pwd(void);//ft_pwd.c
// void ft_cd(const char *input);//ft_cd.c
void ft_cd(char **two_cmd);
void ft_exit(t_mi *mi, char **two_cmd);//ft_exit.c

//***********
typedef enum echo_option 
{
    E_NON,//nonopion
    E_OP,//have option
}   t_echo_option;
void ft_echo(t_mi *mi, char **two_cmd);
t_echo_option check_option(char *op);
//***********

//***********
// t_con *miniparse(char *input);
//***********
//---------------------------------------------
//excute
char **merge_env(t_mi *mi);
char **merge_option(t_mi *mi);//option 리스트로 교체할 예정 입니다.
void exe_cmd(t_mi *mi);
char *real_execute(char **env, char **cmd, char *path);
int check_size(t_mi *mi);
void proc_fork(t_mi *mi);
void proc_fork_2(t_mi *mi, int rf);
void free_two(char **two);
char *return_path(t_mi *mi, char *cmd);
void printf_two(char **str);
// int open_file(char *file, T_RDT re);
//---------------------------------------------
# endif

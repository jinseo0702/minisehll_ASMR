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
int ft_env(t_mi *mi, char **two_cmd);//ft_env.c
bool env_grammar(t_mi *mi, char *val);//ft_env.c
//control_node.c
void insert_node(t_con *env, t_node *new, t_insert_type type);
void remove_node(t_con *env, t_node *target);
//ft_unset.c
t_node *search_node(t_con *env, char *target);
// void ft_unset(t_con *env, char *target);
int ft_unset(t_mi *mi, char **two);
//ft_export.c
// void ft_export(t_con *env, char *val);
int ft_export(t_mi *mi, char **two);
size_t re_two_size(char **two);
void dont_dup(t_mi *mi, char *val);
bool is_dup(t_mi *mi, char *val);
bool exp_grammar(char *val);
bool	ft_arry_grammar_check(char **arry, int idx);

//---------------------------------------------

//prompt관련!!!

void prompt(t_mi *mi);

//---------------------------------------------

//builtins함수들관련 입니다.

t_built_type check_builtins(const char *command);
// void excute_cmd(t_con *env, t_built_type cmd, char *input);
int excute_cmd(t_mi *mi, t_built_type cmd, char **two_cmd);
void control_cmd(t_mi *mi);
int ft_pwd(char **two_cmd);//ft_pwd.c
// void ft_cd(const char *input);//ft_cd.c
int ft_cd(t_mi *mi, char **two_cmd);
void ft_exit(t_mi *mi, char **two_cmd);//ft_exit.c

//***********
typedef enum echo_option 
{
    E_NON,//nonopion
    E_OP,//have option
}   t_echo_option;
int ft_echo(char **two_cmd); // input == echo -n
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
void free_two(char **two);
char *return_path(t_mi *mi, char **cmd);
void printf_two(char **str);
int check_fork(t_mi *mi);
int not_fork(t_mi *mi);
void delete_node(t_mi *mi);
void check_pipe(t_mi *mi, int rf);
void check_mpipe(t_mi *mi, int rf);
// int open_file(char *file, T_RDT re);
//---------------------------------------------

//---------------------------------------------
//re_env.c
void check_env(t_mi *mi);
int check_another2(char *str);
void replace_env(t_pan *pars, t_mi *mi);
char *ft_strjoin_free(char *s1, char *s2);
//test
char *split_env(char *str, t_mi *mi);
int is_alnumbar(char c);
int is_env(char c);
int env_len(char *str);
int check_another3(char *str);
char *change_env(char *str, t_mi *mi);
char *merge_word(t_mi *mi, t_pcon *head);
//---------------------------------------------

//---------------------------------------------
int handle_single_quotes(char *str, char *result, int *i, int *res_idx);
int handle_double_quotes(char *str, char *result, int *i, int *res_idx);
int handle_env_variable(char *str, char *result, int *i, int *res_idx);
char *expand_env_var_with_quotes(char *str);

void	init_terminal(void);
void	restore_terminal(void);
void signal_handler(int signo);
void sigquit_handler(int signo);
void signal_init(void);
//---------------------------------------------
//heredoc
int    play_heredoc(t_pan *current, int pcnt, int tcnt);
char    *str_plus_chr(char *str, char c);
char    *str_plus_str(char *str, char *str2);
void read_get_next(t_pan *current, char *str, int pcnt, int tcnt);
int dup2_std_i(int file_fd);
int open_temp_file(t_pan *current, int pcnt, int tcnt);
void check_heredoc(t_pcon *head);
//---------------------------------------------

//---------------------------------------------
//error
void quotes_syntax_error(void);
void re_syntax_error(char *s);
void another_syntax_error(char *str);
int check_error_case(t_mi *mi);
//---------------------------------------------
# endif

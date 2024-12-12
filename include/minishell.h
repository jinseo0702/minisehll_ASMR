/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:46:02 by jinseo            #+#    #+#             */
/*   Updated: 2024/12/01 11:13:09 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/gnl_check_bonus/get_next_line.h"
# include "../libft/gnl_check_bonus/get_next_line_bonus.h"
# include "./enum_mi.h"
# include "./struct_mi.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <errno.h>

int				ft_cd(t_mi *mi, char **two_cmd);
t_built_type	check_builtins(const char *command);
int				excute_cmd(t_mi *mi, t_built_type cmd, char **two_cmd);
void			control_cmd(t_mi *mi);
t_echo_option	check_option(char *op);
int				ft_echo(char **two_cmd);
int				ft_env(t_mi *mi, char **two_cmd);
void			ft_free_con(t_con *con);
int				is_valid_number(const char *str);
void			ft_free_exit(t_mi *mi);
void			ft_check_exit_error(t_mi *mi, char **two_cmd);
void			ft_exit(t_mi *mi, char **two_cmd);
size_t			re_two_size(char **two);
int				ft_play_export(t_mi *mi, char **two, int idx, int flag);
int				ft_export(t_mi *mi, char **two);
void			dont_dup(t_mi *mi, char *val);
bool			is_dup(t_mi *mi, char *val);
bool			exp_grammar(char *val);
bool			ft_arry_grammar_check(char **arry, int idx);
bool			env_grammar(t_mi *mi, char *val);
int				ft_pwd_error_check(char **two, int idx);
int				ft_pwd(char **two_cmd);
t_node			*search_node(t_con *env, char *target);
int				is_valid_identifier(const char *str);
int				ft_unset(t_mi *mi, char **two);
void			quotes_syntax_error(void);
void			re_syntax_error(char *s);
void			another_syntax_error(char *str);
int				check_error_case(t_mi *mi);
void			execve_e_h(t_mi *mi, char **env, char **cmd, char *path);
void			find_redi(t_mi *mi);
int				change_file_fd(t_mi *mi, t_RDT re);
void			check_redi(t_mi *mi, t_pan *node);
int				open_file(char *file, t_RDT re);
void			handle_e_e(t_mi *mi, char **env, char **cmd, char *path);
int				check_size(t_mi *mi);
int				check_fork(t_mi *mi);
int				not_fork(t_mi *mi);
void			check_mpipe(t_mi *mi, int rf);
void			exe_cmd(t_mi *mi);
void			check_pipe(t_mi *mi, int rf);
void			delete_node(t_mi *mi);
void			free_twice(char *str, char *str2);
int				create_pipe(t_mi *mi, int rf);
void			free_two(char **two);
char			*return_path(t_mi *mi, char **cmd);
char			**merge_env(t_mi *mi);
char			**merge_option(t_mi *mi);
char			*real_execute(char **env, char **cmd, char *path);
void			proc_fork(t_mi *mi);
void			insert_node(t_con *env, t_node *new, t_insert_type type);
void			remove_node(t_con *env, t_node *target);
void			init_con_node(t_con *env, t_node *new, t_linked_type type);
void			ft_free_env(t_con *env);
t_node			*new_node(char *val);
t_con			*init_env(char **envp);
void			init_mi(t_mi *mi, char **envp);
char			*s_env(char *str, t_mi *mi);
int				env_len(char *str);
int				check_another3(char *str);
char			*change_env(char *str, t_mi *mi);
void			check_env(t_mi *mi);
int				check_another2(char *str);
void			replace_env(t_pan *pars, t_mi *mi);
char			*merge_word(t_mi *mi, t_pcon *head);
char			*ft_strjoin_free(char *s1, char *s2);
int				pars(t_mi *mi);
int				is_special(char *s);
int				is_quotes(char c);
int				check_quotes(char *str);
int				check_another(char *str);
void			cnt_pipe(t_mi *mi);
void			ft_free_pcon(t_pcon *env);
t_pan			*new_pan(char *val);
t_in_type		check_type(char *val);
void			print_pcon(t_pcon *head);
void			insert_pan(t_pcon *con, t_pan *new);
t_pan			*search_pan(t_pcon *con, char *target);
ssize_t			re_index_pan(t_pcon *con, t_pan *target);
void			remove_pan(t_pcon *con, t_pan *target);
void			init_pcon_pan(t_pcon *env, t_pan *new, t_clear_type type);
void			check_heredoc(t_pcon *head);
int				play_heredoc(t_pan *current, int pcnt, int tcnt);
char			*ft_file_name(int pcnt, int tcnt);
int				open_temp_file(t_pan *current, int pcnt, int tcnt);
void			free_close(char *temp, int file_fd);
void			read_get_next(t_pan *current, char *str, int pcnt, int tcnt);
void			prompt(t_mi *mi);
void			init_terminal(void);
void			restore_terminal(void);
void			signal_handler(int signo);
void			sigquit_handler(int signo);
void			signal_init(void);
int				is_env(char c);
int				is_alnumbar(char c);
char			*split_env(char *str, t_mi *mi);
char			*process_env_segment(t_mi *mi, char *str, int *end);
char			*s_env(char *str, t_mi *mi);
int				process_input_segment(t_mi *mi, int *idx, int *flag, int *end);
int				handle_parsing(t_mi *mi);

#	endif

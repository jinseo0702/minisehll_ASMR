#ifndef TESTPARSING_H
#define TESTPARSING_H


void print_pcon(t_pcon *head);
t_in_type check_type(char *val);
t_pan *new_pan(char *val);
void ft_free_pcon(t_pcon *env);
void init_pcon_pan(t_pcon *env, t_pan *new, t_clear_type type);
void remove_pan(t_pcon *con, t_pan *target);
ssize_t re_index_pan(t_pcon *con, t_pan *target);
t_pan *search_pan(t_pcon *con, char *target);
void insert_pan(t_pcon *con, t_pan *new);
// t_pcon *miniparse(char *input);
///split_pipe.c
int is_special(char *s);
int is_quotes(char c);
int check_quotes(char *str);
int check_another(char *str);
void cnt_pipe(t_mi *mi);
int pars(t_mi *mi);
#endif
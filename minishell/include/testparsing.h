#ifndef TESTPARSING_H
#define TESTPARSING_H

typedef enum e_in_type
{
    T_PIPE,
    T_REDIRECTION,
    T_ARGV,
    T_ENV,
    T_NULL,
}   t_in_type;

typedef struct s_pan
{
    struct s_pan *next;
    t_in_type type;
    char *val;
} t_pan;

typedef struct s_pcon
{
    struct s_pan *head;
    int size;
} t_pcon;

typedef enum e_clear_type
{
    LINKED_PCON,
    LINKED_PAN
} t_clear_type;

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
t_pcon *pars(char *input);
#endif
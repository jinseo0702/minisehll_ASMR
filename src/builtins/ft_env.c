#include "../../include/minishell.h"

void env_grammar(char *val)
{
    if(ft_strchr(val, '=') && val[0] != '=')
        printf("%s\n", val);
    else
        return ;
}

void ft_env(t_con *env)
{
    t_node *current;

    current = env->head;
    while (current)
    {
        env_grammar(current->val);
        current = current->next;
    }
}

// void ft_env(t_con *env)
// {
//     t_node *current;

//     current = env->head;
//     while (current)
//     {
//         printf("%s\n", current->val);
//         current = current->next;
//     }
// }
#include "../../include/minishell.h"

// void ft_env(t_con *env)
// {
//     t_node *current;

//     current = env->head;
//     while (current)
//     {
//         env_grammar(current->val);
//         current = current->next;
//     }
// }

void ft_env(t_mi *mi)
{
    t_node *current;

    current = mi->env->head;
    while (current)
    {
        printf("%s\n", current->val);
        current = current->next;
    }
}
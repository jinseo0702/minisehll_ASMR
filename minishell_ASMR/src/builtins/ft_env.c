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

void ft_env(t_mi *mi, char **two_cmd)
{
    t_node *current;
    int     idx;

    idx = 0;
    if (two_cmd[++idx])
    {
        printf("env: %s : No such file or directory", two_cmd[idx]);
        return;
    }
    current = mi->env->head;
    while (current)
    {
        printf("%s\n", current->val);
        current = current->next;
    }
}
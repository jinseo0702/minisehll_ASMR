#include "../../include/minishell.h"


void ft_env(t_con *env)
{
    t_node *current;

    current = env->head;
    while (current)
    {
        printf("%s\n", current->val);
        current = current->next;
    }
}
#include "../../include/minishell.h"

int ft_env(t_mi *mi, char **two_cmd)
{
    t_node *current;
    int     idx;

    idx = 0;
    if (two_cmd[++idx])
    {
        printf("env: %s : No such file or directory", two_cmd[idx]);
        return(-100);
    }
    current = mi->env->head;
    while (current)
    {
        printf("%s\n", current->val);
        current = current->next;
    }
    return (100);
}
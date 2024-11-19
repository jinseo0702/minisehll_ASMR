#include "../../include/minishell.h"

t_node *search_node(t_con *env, char *target)
{
    t_node *current;
    int len;

    len = ft_strlen(target);
    current = env->head;
    while (current)
    {
        if (!ft_strncmp(current->val, target, len))
            return (current);     
        current = current->next;
    }
    return (NULL);
}

/*void ft_unset(t_con *env, char *target)
{//문법에 맞지 않는 경우는 어떻게 처리 할지 고민입니다. target이 없는z 경우 처리를 어떻게 할까요?
//아직 예외처리를 하지 않았습니다.
//unset의 옵션이 없어야 하고 인자가 이상한게 들어간 경우 어떻게 처리를 해야할지 처리를 하지 않았습니다.
    remove_node(env, search_node(env, target));
}*/

void ft_unset(t_mi *mi, char **two)
{//문법에 맞지 않는 경우는 어떻게 처리 할지 고민입니다. target이 없는 경우 처리를 어떻게 할까요?
//아직 예외처리를 하지 않았습니다.
//unset의 옵션이 없어야 하고 인자가 이상한게 들어간 경우 어떻게 처리를 해야할지 처리를 하지 않았습니다.
    int idx = 0;
    
    while (two[++idx])
    {
        remove_node(mi->env, search_node(mi->env, two[idx]));
        remove_node(mi->export, search_node(mi->export, two[idx]));
    }
}


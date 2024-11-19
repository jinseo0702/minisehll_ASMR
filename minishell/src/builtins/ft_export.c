#include "../../include/minishell.h"

/*void ft_export(t_con *env, char *val)
{
    insert_node(env, new_node(val), INSERT_TAIL);
}*/
//예외는 아직 고려하지 않고 그냥 노드를 추가하는 함수만 만들었습니다.
//exprot 함수또한 syntex를 지켜야 하기 때문에 이부분에 대한 고민을 해봐야 합니다.
//예를 들면 $표시에 관한 내용이라던가 등등등에 관한 내용을 고려해야 합니다.

bool env_grammar(char *val)
{
    /*if(ft_strchr(val, '=') && val[0] != '=')
        printf("%s\n", val);
    else
        return ;*/
    char **arry;
    int idx;

    idx = 0;
    if(ft_strchr(val, '=') != NULL)
    {
        arry = ft_split(val, '=');
        while (arry[0][idx])
        {
            if (idx == 0 && (ft_isalpha(arry[0][idx]) == 0 && arry[0][idx] != '_'))
            {
                ft_free_two(arry);
                return (false);
            }
            if (ft_isalnum(arry[0][idx]) == 0 && arry[0][idx] != '_')
            {
                ft_free_two(arry);
                return (false);
            }
            idx++;
        }
        ft_free_two(arry);
        return (true);
    }
    return (false);
}

size_t re_two_size(char **two)
{
    size_t siz;

    siz = 0;
    while (two[siz])
        siz++;
    return (siz);
}

void ft_export(t_mi *mi, char **two)//char **two_cmd
{
    t_node *current;
    int idx = 0;
    
    if (re_two_size(two) == 1)
    {
        current = mi->export->head;
        while (current)
        {
            printf("declare -x %s\n", current->val);
            current = current->next;
        }
        return ;
    }
    while (two[++idx])
    {
        if (env_grammar(two[idx]))
        {
            insert_node(mi->env, new_node(ft_strdup(two[idx])), INSERT_TAIL);
            insert_node(mi->export, new_node(ft_strdup(two[idx])), INSERT_TAIL);
        }
        else
            insert_node(mi->export, new_node(ft_strdup(two[idx])), INSERT_TAIL);
    }
}
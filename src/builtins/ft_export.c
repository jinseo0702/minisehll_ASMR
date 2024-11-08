#include "../../include/minishell.h"

/*void ft_export(t_con *env, char *val)
{
    insert_node(env, new_node(val), INSERT_TAIL);
}*/
//예외는 아직 고려하지 않고 그냥 노드를 추가하는 함수만 만들었습니다.
//exprot 함수또한 syntex를 지켜야 하기 때문에 이부분에 대한 고민을 해봐야 합니다.
//예를 들면 $표시에 관한 내용이라던가 등등등에 관한 내용을 고려해야 합니다.

void ft_export(t_con *env, char *val, t_con *test)
{
    t_node *current;
    
    if (test->size == 1)
    {
        current = env->head;
        while (current)
        {
            printf("declare -x %s\n", current->val);
            current = current->next;
        }
        return ;
    }
    test->head = test->head->next;
    current = test->head;
    while (current)
    {
        insert_node(env, new_node(current->val), INSERT_TAIL);
        current = current->next;
    }
}
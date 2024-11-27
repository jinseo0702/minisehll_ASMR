#include "../../include/minishell.h"

void insert_pan(t_pcon *con, t_pan *new)//new타입의 node를 찾는 함수
{
    t_pan *current;

    if (con->head == NULL)
        con->head = new;
    else
    {
        current = con->head;
        while (current->next)
            current = current->next;
        current->next = new;
    }
    con->size++;
}

t_pan *search_pan(t_pcon *con, char *target)//문자열과 같은 값을 가지고 있는 node를 찾습니다.
{
    t_pan *current;
    int len;

    len = ft_strlen(target);
    current = con->head;
    while (current)
    {
        if (!ft_strncmp(current->val, target, len))
            return (current);     
        current = current->next;
    }
    return (NULL);
}

ssize_t re_index_pan(t_pcon *con, t_pan *target)//target_node가 몇번째에 들어 있는 지 알려줌
{
    size_t idx;
    t_pan *current;

    idx = 0;
    current = con->head;
    while (current)
    {
        if (&*current == &*target)
            return (idx);
        current = current->next;
        idx++;
    }
    return (-1);
}

void remove_pan(t_pcon *con, t_pan *target)//target_node를 삭제해줍니다.
{
    int idx;
    int idx2;
    t_pan *current;

    // printf("size == %s \n", con->head->val);
    idx = re_index_pan(con, target);
    idx2 = 0;
    if (target == NULL)
        return ; //이에러 처리 즉 어떻게 할지 고민입니다.
    if (idx == -1)//없는 경우 에러처리
        return ;
    else if (idx == 0)
        con->head = con->head->next;
    else
    {
        current = con->head;
        while (++idx2 < idx)
            current = current->next;
        current->next = target->next;
    }
    ft_freenull(&(target->val));
    free(target);
    target = NULL;
    con->size--;
}

void init_pcon_pan(t_pcon *env, t_pan *new, t_clear_type type)//초기화 해줍니다.
{
    if (type == LINKED_PCON)
    {
        env->head = NULL;
        env->size = 0;
    }
    else if (type == LINKED_PAN)
    {
        new->next = NULL;
        new->val = NULL;
        new->type = T_NULL;
    }
}

void ft_free_pcon(t_pcon *env)
{
    t_pan *temp;
    t_pan *next;

    temp = env->head;
    while (temp)
    {
        next = temp->next;
        ft_freenull(&(temp->val));
        free(temp);
        temp = next;
        env->size--;
    }
    env->head = NULL;
    free(env);
    env = NULL;
}

t_pan *new_pan(char *val)
{
    t_pan *new;
    new = (t_pan *)malloc(sizeof(t_pan));
    if (!new)
    {
        //error처리는 어떻게 하지 의논해야 합니다.
        printf("assignment fail!\n");
        exit(1);
    }
    init_pcon_pan(NULL, new, LINKED_PAN);
    new->val = val;
    new->type = check_type(val);
    return (new);
}

t_in_type check_type(char *val)
{
    if (!ft_strncmp(val, "|", 1) && ft_strlen(val) == 1)
        return (T_PIPE);
    else if (!ft_strncmp(val, ">>", 2) && ft_strlen(val) == 2)
        return (T_REDIRECTION);
    else if (!ft_strncmp(val, "<<", 2) && ft_strlen(val) == 2)
        return (T_REDIRECTION);
    else if (!ft_strncmp(val, "<", 1) && ft_strlen(val) == 1)
        return (T_REDIRECTION);
    else if (!ft_strncmp(val, ">", 1) && ft_strlen(val) == 1)
        return (T_REDIRECTION);
    else
        return (T_ARGV);
}

void print_pcon(t_pcon *head)
{
    t_pan *current;
    const char *type[] = {"T_PIPE", "T_REDIRECTION", "T_ARGV", "T_ENV", "T_NULL"};
    current = head->head;
    while (current)
    {
        printf("val : %s\n", current->val);
        printf("type : %s\n", type[current->type]);
        current = current->next;
    }
}

// int main(void)
// {
//     t_mi mi;
//     mi.input = readline(">? ");
//     pars(&mi);
//     free(mi.input);
//     ft_free_pcon(mi.head);
//     return (0);
// }


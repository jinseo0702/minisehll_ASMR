#include "../../include/minishell.h"
//이부분은 확실하게 파싱의 틀이 잡혀야지 진행이 가능하다.

t_echo_option check_option(char *op)
{
    if (*op != '-')
        return (E_NON);
    op++;
    while (*op)
    {
        if (*op != 'n')
            return (E_NON);
        op++;
    }
    return (E_OP);
}

void ft_echo(char *input, t_con *test) //input == echo -n 
{
    (void *)input;
    t_node *current;
    int flag = 0;
    t_echo_option option;

    test->head = test->head->next;//test용도 입니다.
    current = test->head;
    option = E_NON;
    while (current)
    {
        if (!flag && check_option(current->val) == E_OP)
            option = E_OP;
        if (check_option(current->val) == E_NON)
            break;
        current = current->next;
        flag++;
    }
    while (current)
    {
        printf ("%s", current->val);
        if (current->next != NULL)
                printf (" ");
        current = current->next;
    }
    if (option == E_NON)
        printf ("\n");
}
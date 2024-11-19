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

void ft_echo(t_mi *mi, char **two_cmd) //input == echo -n 
{
    (void)mi;//$처리하기 아직 yet
    int idx = 0;
    int flag = 0;
    t_echo_option option;

    option = E_NON;
    while (two_cmd[++idx])
    {
        if (!flag && check_option(two_cmd[idx]) == E_OP)
            option = E_OP;
        if (check_option(two_cmd[idx]) == E_NON)
            break;
        flag++;
    }
    while (two_cmd[idx])
    {
        printf ("%s", two_cmd[idx]);
        printf (" ");
        idx++;
    }
    if (option == E_NON)
        printf ("\n");
}
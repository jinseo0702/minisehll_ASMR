#include "../../include/minishell.h"

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

int ft_echo(char **two_cmd)
{
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
        if (two_cmd[idx + 1] != NULL)
            printf (" ");
        idx++;
    }
    if (option == E_NON)
        printf ("\n");
    return (100);
}
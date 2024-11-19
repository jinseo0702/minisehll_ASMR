#include "../../include/minishell.h"

void ft_exit(t_mi *mi, char **two_cmd)
{//누수 또한 생각을 해줘야 합니다.
    (void)mi;
    (void)two_cmd;
    printf("end shell\n");//test용 입니다.
    exit(0);
}
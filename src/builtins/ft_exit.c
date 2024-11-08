#include "../../include/minishell.h"

void ft_exit(char *input)
{//누수 또한 생각을 해줘야 합니다.
    printf("end shell\n");//test용 입니다.
    free(input);
    exit(0);
}
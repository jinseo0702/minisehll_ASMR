#include "../include/minishell.h"

void prompt(void)
{
    char *input;

    while (input = readline("~$ ") != NULL)
    {
        add_history(input);
        /*else*/ if (ft_strncmp)
    }
}
#include "../../include/minishell.h"

int is_special(char *s)
{
    if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, "<<", 2))
        return (2);
    else if (!ft_strncmp(s, "<", 1) || !ft_strncmp(s, "<", 1) || !ft_strncmp(s, "|", 1))
        return (1);
    else
        return (0);
}

void check(char *input)
{
    int idx = 0;
    int size = 0;

    while (input[idx])
    {
        if (is_special(input[idx]))
        {
            size = is_special(input[idx]);
        }

        idx++;
    }
}
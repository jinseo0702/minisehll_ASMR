#include "../include/minishell.h"

int main(int argc, char **argv)
{
    int idx = 0;
    char **str = ft_split(argv[1], ',');
    (void)argc;
    while (str[idx] != NULL)
    {
        printf("%s\n", str[idx]);
        idx++;
    }
    
    return (0);
}
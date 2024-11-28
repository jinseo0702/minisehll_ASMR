#include "../../include/minishell.h"

void free_two(char **two)
{
    int idx;

    idx = 0;
    while (two[idx])
    {
        free(two[idx]);
        idx++;
    }
    free(two);
}

char *return_path(t_mi *mi, char **cmd)
{
    char *path_real;
    char *path_real2;
    char **split;
    int idx;

    idx = 0;
    if (!ft_strncmp(*cmd, "", 1))
        return (ft_strdup(*cmd));
    split = ft_split(ft_strchr(search_node(mi->env, "PATH")->val, '/'), ':');
    while (split[idx])
    {
        path_real = ft_strjoin(split[idx], "/");
        path_real2 = ft_strjoin(path_real, *cmd);
        if (access(path_real2, F_OK) == 0)
        {
            free_two(split);
            free(path_real);
            return(path_real2);
        }
        free(path_real);
        free(path_real2);
        idx++;
    }
    free_two(split);
    return (ft_strdup(*cmd));
}
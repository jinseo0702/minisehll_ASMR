#include "../../include/minishell.h"

t_built_type check_builtins(const char *command)
{
    if (ft_strncmp("echo", command, 4) && ft_strlen(command) == 4)
        return (BUILT_ECHO);
    else if (ft_strncmp("cd", command, 2) && ft_strlen(command) == 2)
        return (BUILT_CD);
    else if (ft_strncmp("pwd", command, 3) && ft_strlen(command) == 3)
        return (BUILT_PWD);
    else if (ft_strncmp("export", command, 6) && ft_strlen(command) == 6)
        return (BUILT_EXPORT);
    else if (ft_strncmp("unset", command, 5) && ft_strlen(command) == 5)
        return (BUILT_UNSET);
    else if (ft_strncmp("env", command, 3) && ft_strlen(command) == 3)
        return (BUILT_ENV);
    else if (ft_strncmp("exit", command, 4) && ft_strlen(command) == 4)
        return (BUILT_EXIT);
    else
        return (BUILT_NOT);
}

void excute_cmd(t_con *env, t_built_type cmd, char *input)
{
    if (cmd == BUILT_ECHO)
        return ;
    else if (cmd == BUILT_CD)
        return ;
    else if (cmd == BUILT_PWD)
        ft_pwd();
    else if (cmd == BUILT_EXPORT)
        ft_export(env, input);
    else if (cmd == BUILT_UNSET)
        ft_unset(env, input);
    else if (cmd == BUILT_ENV)
        ft_env(env);
    else if (cmd == BUILT_EXIT)
        return ;
    else if (cmd == BUILT_NOT)
        printf ("What is this ??? \n");
}

void control_cmd(t_con *env, const char *command, char *input)
{
    excute_cmd(env, check_builtins(command), input);
}
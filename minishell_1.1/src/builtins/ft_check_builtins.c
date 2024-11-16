#include "../../include/minishell.h"

t_built_type check_builtins(const char *command)
{
    if (!ft_strncmp("echo", command, 4) && ft_strlen(command) == 4)
        return (BUILT_ECHO);
    else if (!ft_strncmp("cd", command, 2) && ft_strlen(command) == 2)
        return (BUILT_CD);
    else if (!ft_strncmp("pwd", command, 3) && ft_strlen(command) == 3)
        return (BUILT_PWD);
    else if (!ft_strncmp("export", command, 6) && ft_strlen(command) == 6)
        return (BUILT_EXPORT);
    else if (!ft_strncmp("unset", command, 5) && ft_strlen(command) == 5)
        return (BUILT_UNSET);
    else if (!ft_strncmp("env", command, 3) && ft_strlen(command) == 3)
        return (BUILT_ENV);
    else if (!ft_strncmp("exit", command, 4) && ft_strlen(command) == 4)
        return (BUILT_EXIT);
    else
        return (BUILT_NOT);
}

void excute_cmd(t_mi *mi, t_con *env, t_built_type cmd, char *input, t_con *test)
{
    if (cmd == BUILT_ECHO)
        return ft_echo(mi, test);
    else if (cmd == BUILT_CD)
        ft_cd(input, test);
    else if (cmd == BUILT_PWD)
        ft_pwd();
    else if (cmd == BUILT_EXPORT)
        ft_export(mi, test);
    else if (cmd == BUILT_UNSET)
        ft_unset(env, input, test);
    else if (cmd == BUILT_ENV)
        ft_env(mi);
    else if (cmd == BUILT_EXIT)
        return (ft_exit(input));
    else if (cmd == BUILT_NOT)
        return(exe_cmd(env, test));
}

void control_cmd(t_mi *mi, t_con *env, const char *command, char *input)
{
    t_con *test = miniparse(input);
    (void *)command;
    excute_cmd(mi, env, check_builtins(test->head->val), input, test);
}
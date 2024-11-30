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

int excute_cmd(t_mi *mi, t_built_type cmd, char **two_cmd)
{
    if (cmd == BUILT_ECHO)
        return(ft_echo(two_cmd));
    else if (cmd == BUILT_CD)
        return(ft_cd(mi, two_cmd));
    else if (cmd == BUILT_PWD)
        return(ft_pwd(two_cmd));
    else if (cmd == BUILT_EXPORT)
        return(ft_export(mi, two_cmd));
    else if (cmd == BUILT_UNSET)
        return(ft_unset(mi, two_cmd));
    else if (cmd == BUILT_ENV)
        return(ft_env(mi, two_cmd));
    else if (cmd == BUILT_EXIT)
    {
        ft_exit(mi, two_cmd);
        return (100);
    }
    else if (cmd != BUILT_NOT)
        return (100);
    return (100);
}

void control_cmd(t_mi *mi)
{
    if (pars(mi) < 0)
        return ;
    if (mi->head->size == 0)
        return ;
    if (check_error_case(mi) < 0)
        return ;
    check_env(mi);
    check_heredoc(mi->head);
    proc_fork(mi);
}

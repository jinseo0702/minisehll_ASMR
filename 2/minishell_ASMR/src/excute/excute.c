#include "../../include/minishell.h"

void handle_execve_error(t_mi *mi, char **env, char **cmd, char *path)
{
    if (errno == EACCES)
    {
        execve_error_handle(mi, env, cmd, path);
        ft_putendl_fd(": Permission denied", 2);
        exit(126);
    }
    else if (errno == ENOENT)
    {
        execve_error_handle(mi, env, cmd, path);
        ft_putendl_fd(": command not found", 2);
        exit(127);
    }
    else if (errno == EISDIR)
    {
        execve_error_handle(mi, env, cmd, path);
        ft_putendl_fd(": Is a directory", 2);
        exit(126);
    }
    else
    {
        execve_error_handle(mi, env, cmd, path);
        ft_putendl_fd(": Execution failed", 2);
        exit(1); 
    }
}

int check_size(t_mi *mi)
{
    t_pan *current;
    int cnt;

    cnt = 0;
    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        cnt++;
        current = current->next;
    }
    return (cnt);
}

int check_fork(t_mi *mi)
{
    t_pan *current;
    char *path;

    current = mi->head->head;
    while (current)
    {
        if (current->type == T_REDIRECTION)
        {
            current = current->next;
            current = current->next;
        }
        else
        {
            break;
        }
    }
    if (!current)
        return (1);
    if (check_builtins(current->val) == BUILT_NOT)
        return (0);
    return (1);
}

int not_fork(t_mi *mi)
{
    int std_i;
    int std_o;

    std_i = dup(0);
    std_o = dup(1);
    if (std_i == -1 || std_o == -1)
        return (-1);
    exe_cmd(mi);
    if (dup2(std_i, 0) == -1 || dup2(std_o, 1) == -1)
        return (-1);
    close(std_i);
    close(std_o);
    mi->of = 0;
    return (1);
}

void check_mpipe(t_mi *mi, int rf)
{
    if (mi->pcnt > 0 && rf < mi->pcnt)
    {
        if (rf > 0)
            close(mi->temp_fd);
        if((mi->temp_fd = dup(mi->fd[0])) == -1)
            exit(1);
        close(mi->fd[0]);
        close(mi->fd[1]);
    }
    else if (mi->pcnt > 0 && rf == mi->pcnt)
    {
        close(mi->temp_fd);
        close(mi->fd[0]);
        close(mi->fd[1]);
    }
    return ;
}

void check_pipe(t_mi *mi, int rf)
{
    int err_i = 0;
    int err_o = 0;

    if (rf == 0)
        err_o = dup2(mi->fd[1], STDOUT_FILENO);
    else if (rf > 0 && rf < mi->pcnt)
    {
        err_i = dup2(mi->temp_fd, STDIN_FILENO);
        err_o = dup2(mi->fd[1], STDOUT_FILENO);
        close(mi->temp_fd);
    }
    else
    {
        err_i = dup2(mi->temp_fd, STDIN_FILENO);
        close(mi->temp_fd);
    }
    if (err_i == -1 || err_o == -1)
        exit(1);
    close(mi->fd[0]);
    close(mi->fd[1]);
}

void delete_node(t_mi *mi)
{
    t_pan *current;

    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        remove_pan(mi->head, current);
        current = mi->head->head;
    }
    if (current->type == T_PIPE)
        remove_pan(mi->head, current);
    return ;
}
#include "../../include/minishell.h"

void init_mi(t_mi *mi, char **envp)
{
    mi->env = init_env(envp);
    mi->export = init_env(envp);
    mi->input = NULL;
    mi->head = NULL;
    mi->file = 0;
    mi->pcnt = 0;
    mi->exit_status = 0;
    ft_bzero(mi->fd, 2);
    mi->temp_fd = 0;
    mi->dup = 0;
    mi->pid = -100;
    mi->of = 0;
}

int main(int argc, char **argv, char **envp)
{
    t_mi mi;

    init_mi(&mi, envp);
    prompt(&mi);
    return (0);
}
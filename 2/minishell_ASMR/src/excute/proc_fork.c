#include "../../include/minishell.h"

static int handle_initial_fork(t_mi *mi)
{
    if (mi->pcnt == 0)
    {
        if (check_fork(mi) == 1)
        {
            if (not_fork(mi) == -1)
            {
                printf("fatal error stdin_out dup error!!\n");
                exit(1);
            }
            return (1);
        }
    }
    return (0);
}

static void handle_child_process(t_mi *mi, int rf)
{
    if (mi->pcnt > 0)
        check_pipe(mi, rf);
    mi->dup = 1;
    exe_cmd(mi);
    ft_freenull((&mi->input));
    ft_free_env(mi->env);
    ft_free_env(mi->export);
    exit(0);
}

static void handle_parent_process(t_mi *mi, int rf)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    if (mi->pcnt > 0 && rf < mi->pcnt)
        delete_node(mi);
    check_mpipe(mi, rf);
}

static void handle_exit_status(t_mi *mi, pid_t last_pid)
{
    int status;
    int signo = 0;
    int wpid;

    while ((wpid = waitpid(-1, &status, 0)) > 0)
    {
        if (wpid == last_pid)
        {
            if (WIFEXITED(status))
                mi->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
            {
                mi->exit_status = 128 + WTERMSIG(status);
                signo = mi->exit_status - 128;
            }
        }
    }

    if (signo == SIGINT)
        printf("^C\n");
    if (signo == SIGQUIT)
        printf("^Quit (core dumped)\n");
}

void proc_fork(t_mi *mi)
{
    int rf = -1;
    int last_pid;

    if (handle_initial_fork(mi) == 1)
        return;
    while (rf < mi->pcnt)
    {
        rf++;
        if (mi->pcnt > 0 && rf < mi->pcnt)
        {
            if(pipe(mi->fd) == -1)
                exit(1);
        }
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        mi->pid = fork();
        if (rf == mi->pcnt)
            last_pid = mi->pid;
        if (mi->pid == -1)
            exit(1);
        else if (mi->pid == 0)
            handle_child_process(mi, rf);
        else
            handle_parent_process(mi, rf);
    }
    handle_exit_status(mi, last_pid);
}
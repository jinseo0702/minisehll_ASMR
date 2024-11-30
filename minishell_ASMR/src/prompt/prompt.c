#include "../../include/minishell.h"

#include "../../include/minishell.h"

static void init_terminal(void)
{
    struct termios term;
    
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// 프로그램 종료 시
static void restore_terminal(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void signal_handler(int signo)
{
    restore_terminal();
    if (signo == SIGINT)
    {
        if (isatty(STDIN_FILENO))
        {
            write(STDOUT_FILENO, "\n", 1);
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
        }
    }
}
void sigquit_handler(int signo)
{
    init_terminal();
    if (signo == SIGQUIT)
    {
        rl_on_new_line();
        rl_redisplay();
    }
}
void signal_init(void)
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        perror("signal error for SIGINT");
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("signal error for SIGQUIT");
}

void prompt(t_mi *mi)
{
    while (1)
    {
        restore_terminal();
        signal_init();
        if ((mi->input = readline("~$ ")) != NULL)
        {
            init_terminal();
            add_history(mi->input);
            rl_redisplay();
            control_cmd(mi);
        }
        else
        {
            ft_freenull((&mi->input));
            ft_free_env(mi->env);
            ft_free_env(mi->export);
            exit(0);
        }
        ft_freenull(&(mi->input));
        ft_free_pcon(mi->head);
        mi->pcnt = 0;
		mi->file = 0;
    }
}
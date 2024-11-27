#include "../../include/minishell.h"

char    *str_plus_chr(char *str, char c)
{
    char    *buf;
    int     i;

    if (!str)
        return (0);
        buf = malloc(sizeof (char) * ft_strlen(str) + 2);
        if (buf)
        {
            i = 0;
            while (str[i++])
                buf[i] = str[i];
            buf[i] = c;
            buf[i + 1] = '\0';
        }
        free(str);
        return (buf);
}

char    *str_plus_str(char *str, char *str2)
{
    char    *buf;

    buf = str;
    str = ft_strjoin(str, str2);
    free(buf);
    return (str);
}

char *heredoc_readline(char *limiter)
{
    char    *now_str;
    char    *return_str;

    signal(SIGINT, signal_ctlc_heredoc);
    return_str = malloc(1);
    if (!return_str)
        return (0);
    now_str = readline("> ");
    while (now_str && ft_strncmp(now_str, limiter, ft_strlen(limiter) + 1))
    {
        now_str = str_plus_chr(now_str, '\n');
        if (!now_str)
        {
            free(return_str);
            printf("minishell: Out of memory");
            return (0);
        }
        return_str = str_plus_str(return_str, now_str);
        if (!return_str)
            break ;
        free (return_str);
        now_str = readline("> ");
    }
    free (now_str);
    return (return_str);
    
}

int lay_out_heredoc(char *val, char **limiter)
{
    int fd;

    fd = dup(STDIN_FILENO);
    if (fd == -1)
    {
        printf("minishell: Bad file descriptor");
        return (1);
    }
    free(val);
    if (isatty(STDIN_FILENO))
        val = heredoc_readline(*limiter);
    else
    {
        printf("minishell: Bad file descriptor");
        return (1);
    }
    if (errno = EBADF)
    {
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            printf("minishell: Bad file descriptor");
            return (1);
        }
    }
    close(fd);
    if (val)
    {
        printf("minishell: Out of memory");
        return (1);
    }
}


int    play_heredoc(char *val)
{
    char    *limiter;

    if (!val)
    {
        printf("heredoc: syntax error near unexpected token `newline'");
        return (1);

    }
    limiter = ft_strjoin(limiter, val);
    if (!limiter)
    {
        printf("heredoc: memory allocation error\n");
        return (1);
    }
    if (lay_out_heredoc(val, &limiter))
    {
        free(limiter);
        return (1);
    }
    free(limiter);
    return (0);
}

//ft_freenull(val);//free가 필요한지 안한지를 아직 모르겠움.
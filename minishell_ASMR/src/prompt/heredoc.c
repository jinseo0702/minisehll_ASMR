#include "../../include/minishell.h"

int    play_heredoc(t_pan *current, int pcnt, int tcnt)
{
    char    *limiter;
    // int std_in;

    // if ((std_in = dup(STDOUT_FILENO)) == -1)
    // {
    //     printf("minishell: Bad file descriptor");
    //     return (1);
    // }
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    if (!current->val)
    {
        printf("heredoc: syntax error near unexpected token `newline'");
        return (1);

    }
    limiter = ft_strdup(current->val);
    if (!limiter)
    {
        printf("heredoc: memory allocation error\n");
        return (1);
    }
    read_get_next(current, limiter, pcnt, tcnt);
    ft_freenull(&limiter);
    // if (dup2(std_in, STDOUT_FILENO) == -1)
    // {
    //     printf("minishell: Bad file descriptor");
    //     close(std_in);
    //     return (1);
    // }
    // close(std_in);
    return (0);
}

int open_temp_file(t_pan *current, int pcnt, int tcnt)
{
    int file;
    char *temp;
    char *temp2;
    char *file_name;
    char *i_pcnt;
    char *i_tcnt;

    i_pcnt = ft_itoa(pcnt);
    i_tcnt = ft_itoa(tcnt);
    temp = ft_strjoin(i_pcnt, "_");
    temp2 = ft_strjoin(temp, i_tcnt);
    file_name = ft_strjoin(".temp_", temp2);
    file = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0633);
    if (file == -1)
        return (file);//error처리 해야합니다.
    ft_freenull(&i_pcnt);
    ft_freenull(&i_tcnt);
    ft_freenull(&temp);
    ft_freenull(&temp2);
    ft_freenull(&current->val);
    current->val = ft_strdup(file_name);
    ft_freenull(&file_name);
    return (file);
}

// int dup2_std_i(int file_fd)
// {
//     if (dup2(file_fd, STDOUT_FILENO) == -1)
//     {
//         return (-1);//error처리
//     }
//     return (1);
// }

void read_get_next(t_pan *current, char *str, int pcnt, int tcnt)
{
    char *temp;
    int file_fd;

    file_fd = open_temp_file(current, pcnt, tcnt);
    // dup2_std_i(file_fd);
    while (1)
    {
        ft_putstr_fd("> ", 1);
        temp = get_next_line(0);
        if (temp == NULL)
        {
            ft_putstr_fd("minishell: warning: here-document at line delimited by end-of-file (wanted `eof')\n", 2);
            ft_freenull(&temp);
            close(file_fd);
            return;
        }
        ft_putstr_fd(temp, file_fd);
        if(!ft_strncmp(temp, str, ft_strlen(str)) && temp[ft_strlen(str)] == '\n')
        {
            ft_freenull(&temp);
            close(file_fd);
            return ;
        }
        ft_freenull(&temp);
    }
}

void check_heredoc(t_pcon *head)
{
    t_pan *current;
    int pcnt;
    int tcnt;

    pcnt = 0;
    tcnt = 0;
    current = head->head;
    while (current)
    {
        if (current->type == T_PIPE)
            pcnt++;
        if (current->type == T_REDIRECTION)
        {
            if (!ft_strncmp("<<", current->val, 2))
            {
                tcnt++;
                play_heredoc(current->next, pcnt, tcnt);
            }   
        }
        current = current->next;
    }
}
//ft_freenull(val);//free가 필요한지 안한지를 아직 모르겠움.
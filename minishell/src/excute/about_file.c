#include "../../include/minishell.h"

void find_redi(t_mi *mi)
{
    t_pan *current;
    int cnt = 0;

    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        if (current->type == T_REDIRECTION)
        {
            check_redi(mi, current);
            current = mi->head->head;
        }
        current = current->next;
    }
    return ;
}

int change_file_fd(t_mi *mi, T_RDT re)
{
    int fd;

    if (re == T_DGREAT || re == T_GREAT)
        fd = dup2(mi->file, STDOUT_FILENO);
    else if(re == T_LESS)
        fd = dup2(mi->file, STDIN_FILENO);
    close(mi->file);
    return(fd);
}

void check_redi(t_mi *mi, t_pan *node)
{
    T_RDT re;
    t_pan *temp;

    if (!ft_strncmp(">>", node->val, 2))
        mi->file = open_file(node->next->val, (re = T_DGREAT));
    else if (!ft_strncmp("<<", node->val, 2))
        mi->file = open_file(node->next->val, (re = T_DLESS));
    else if (!ft_strncmp("<", node->val, 1))
        mi->file = open_file(node->next->val, (re = T_LESS));
    else if (!ft_strncmp(">", node->val, 1))
        mi->file = open_file(node->next->val, (re = T_GREAT));
    temp = node->next;
    remove_pan(mi->head, node);
    remove_pan(mi->head, temp);
    // print_pcon(mi->head);
    if (change_file_fd(mi, re) == -1)
    {
        printf("error 처리 하기!!!\n");
    }
}

int open_file(char *file, T_RDT re)
 {
    int fd;

    if (re == T_LESS)
        fd = open(file, O_RDONLY, 0644);
    else if (re == T_GREAT)
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (re == T_DGREAT)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        printf("error !!\n");
    return (fd);
}
#include "../../include/minishell.h"

void find_redi(t_mi *mi)
{
    t_pan *current;

    current = mi->head;
    while (current || current->type != T_PIPE)
    {
        if (current->type == T_REDIRECTION)

        current = current->next;
    }
}

int built_fd(t_mi *mi)
{}

void check_redi(t_mi *mi, t_pan *node)
{
    T_RDT re;

    if (!ft_strncmp(">>", node->val, 2))
        mi->file = open_file(node->next, (re = T_DGREAT));
    else if (!ft_strncmp("<<", node->val, 2))
        mi->file = open_file(node->next, (re = T_DLESS));
    else if (!ft_strncmp("<", node->val, 1))
        mi->file = open_file(node->next, (re = T_LESS));
    else if (!ft_strncmp(">", node->val, 2))
        mi->file = open_file(node->next, (re = T_GREAT));
    remove_pan(mi, node);
    remove_pan(mi, node->next);
    if (built_fd(mi))
    {}
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
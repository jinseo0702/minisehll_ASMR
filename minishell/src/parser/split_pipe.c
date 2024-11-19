#include "../../include/minishell.h"

int is_special(char *s)
{
    if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
        return (2);
    else if (!ft_strncmp(s, "<", 1) || !ft_strncmp(s, ">", 1) || !ft_strncmp(s, "|", 1))
        return (1);
    else
        return (0);
}

int is_quotes(char c)
{
    if (c == '\'' || c == '"')
        return (c);
    else
        return (0);
}

int check_quotes(char *str)
{
    char q_type;
    int idx;

    q_type = *str;
    idx = 0;
    while (str[++idx])
    {
        if (str[idx] == q_type)
            return (++idx);
    }
    return (-1);//따옴쵸가 
}

int check_another(char *str)
{
    int idx;
    int end;

    idx = 0;
    while (str[idx] && !ft_isspace(str[idx]) && !is_special(&str[idx]))
    {
        end = 0;
        if (is_quotes(str[idx]))
        {
            idx += check_quotes(&str[idx]);
            // return(idx);
        }
        else
        {
            idx++;
        }
    }
    return(idx);    
}

void cnt_pipe(t_mi *mi)
{
    t_pan *current;

    current = mi->head->head;
    while (current)
    {
        if (current->type == T_PIPE)
            mi->pcnt++;
        current = current->next;
    }
}

void pars(t_mi *mi)
{
    mi->head = malloc(sizeof(t_pcon));
    init_pcon_pan(mi->head, NULL, LINKED_PCON);
    int idx;
    int end;

    idx = 0;
    while (mi->input[idx])
    {
        end = 0;
        if (ft_isspace(mi->input[idx]))
        {
            idx++;
            continue;
        }
        else if (is_quotes(mi->input[idx]))
        {
           end = check_quotes(&mi->input[idx]);
           if (end == -1)
            break;
        }
        else if (is_special(&mi->input[idx]))
            end += is_special(&mi->input[idx]);
        else
        {
            end += check_another(&mi->input[idx]);
        }
        insert_pan(mi->head, new_pan(ft_substr(mi->input, idx, end)));
        idx += end;
    }
    cnt_pipe(mi);
    // print_pcon(mi->head);
    // printf("cnt is = %d \n", mi->pcnt);
}

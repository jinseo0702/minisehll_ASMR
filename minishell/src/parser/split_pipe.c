#include "../../include/minishell.h"

int is_special(char *s)
{
    if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
        return (2);
    else if (!ft_strncmp(s, "<", 1) || !ft_strncmp(s, "<", 1) || !ft_strncmp(s, "|", 1))
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

t_pcon *pars(char *input)
{
    t_pcon *head = malloc(sizeof(t_pcon));
    init_pcon_pan(head, NULL, LINKED_PCON);
    int idx;
    int end;

    idx = 0;
    while (input[idx])
    {
        end = 0;
        if (ft_isspace(input[idx]))
        {
            idx++;
            continue;
        }
        else if (is_quotes(input[idx]))
        {
           end = check_quotes(&input[idx]);
           if (end == -1)
            break;
        }
        else if (is_special(&input[idx]))
            end += is_special(&input[idx]);
        else
        {
            end += check_another(&input[idx]);
        }
        insert_pan(head, new_pan(ft_substr(input, idx, end)));
        idx += end;
    }
    print_pcon(head);
    return(head);
}

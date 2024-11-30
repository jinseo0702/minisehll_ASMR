/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rp_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:13:16 by jinseo            #+#    #+#             */
/*   Updated: 2024/11/26 20:13:17 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void check_env(t_mi *mi)
{
   t_pan *current;
   
   current = mi->head->head;
   while (current)
   {
    if (current->type == T_ARGV)
    {
        replace_env(current, mi);
    }
    current = current->next;
   }
}

int check_another2(char *str)
{
    int idx;

    idx = 1;
    while (str[idx] && !is_quotes(str[idx]))
            idx++;
    return(idx);    
}

void replace_env(t_pan *pars, t_mi *mi)
{
    t_pcon *head;
    int idx;
    int end;

    idx = 0;
    head = malloc(sizeof(t_pcon));
    init_pcon_pan(head, NULL, LINKED_PCON);
    while (pars->val[idx])
    {
        end = 0;
        if (is_quotes(pars->val[idx]))
        {
           end = check_quotes(&pars->val[idx]);
           if (end == -1)
            break;
        }
        else
        {
            end += check_another2(&pars->val[idx]);
        }
        insert_pan(head, new_pan(ft_substr(pars->val, idx, end)));
        idx += end;
    }
    ft_freenull(&(pars->val));
    pars->val = merge_word(mi, head);
    ft_free_pcon(head);
}

char *merge_word(t_mi *mi, t_pcon *head)
{
    t_pan *current;
    char *temp = NULL;

    current = head->head;
    while (current)
    {
        temp = ft_strjoin_free(temp, change_env(current->val, mi));
        current = current->next;
    }
    return (temp);
}


char *ft_strjoin_free(char *s1, char *s2)
{
    char *temp;

    if (s1 == NULL)
        s1 = ft_strdup("");
    if (s2 == NULL)
        s2 = ft_strdup("");
    temp = ft_strjoin(s1, s2);
        ft_freenull(&s1);
        ft_freenull(&s2);
    return (temp);
}

char *s_env(char *str, t_mi *mi)
{
    char *temp;
    t_node *tmp;

    tmp = search_node(mi->env, &str[1]);
    if (tmp == NULL)
    {
        ft_freenull(&str);
        return (NULL);
    }
    if (ft_strchr(tmp->val, '='))
    {
        temp = ft_strdup(ft_strchr(tmp->val, '=') + 1);
        ft_freenull(&str);
        return (temp);
    }
    ft_freenull(&str);
    return (NULL);
}

char *split_env(char *str, t_mi *mi)
{
    char *temp = NULL;
    char *temp_env;
    int idx;
    int end;

    idx = 0;
    while (str[idx])
    {
        end = 0;
        if (!ft_strncmp(&str[idx], "$?", 2))
        {
            end = 2;
            temp_env = ft_itoa(mi->exit_status);
        }
        else if (is_env(str[idx]))
        {
           end = env_len(&str[idx]);
           if (end == -1)
            break;
            if (end > 1)
                temp_env = s_env(ft_substr(str, idx, end), mi);
            else
                temp_env = ft_substr(str, idx, end);
        }
        else
        {
            end += check_another3(&str[idx]);
            temp_env = ft_substr(str, idx, end);
        }
        temp = ft_strjoin_free(temp, temp_env);
        idx += end;
    }
    return (temp);
}

int is_alnumbar(char c)
{
    int e;

    e = ft_isalnum(c);
    if (e == 0)
    {
        if (c == '_')
            return (c);
    }
    return (e);
}

int is_env(char c)
{
    if (c == '$')
        return (c);
    else
        return (0);
}

int env_len(char *str)
{
    int idx;

    idx = 1;
    while (str[idx])
    {
        if (is_alnumbar(str[idx]) && !ft_isspace(str[idx]))
            idx++;
        else 
            return (idx);
    }
    return (idx);
}

int check_another3(char *str)
{
    int idx;

    idx = 1;
    while (str[idx] && !is_env(str[idx]))
            idx++;
    return(idx);    
}

char *change_env(char *str, t_mi *mi)
{
    char *temp;
    char *temp2;

    if (is_quotes(*str) == '\'')
        return (ft_strtrim(str, "\'"));
    else
    {
        if (is_quotes(*str) == '\"')
        {
           temp = ft_strtrim(str, "\"");
           temp2 = split_env(temp, mi);
           ft_freenull(&temp);
           return(temp2);
           
        }
        else
        {
            return(split_env(str, mi));
        }
    }
}
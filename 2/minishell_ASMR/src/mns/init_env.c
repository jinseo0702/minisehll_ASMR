#include "../../include/minishell.h"

void init_con_node(t_con *env, t_node *new, t_linked_type type)
{
    if (type == LINKED_CON)
    {
        env->head = NULL;
        env->tail = NULL;
        env->size = 0;
    }
    else if (type == LINKED_NODE)
    {
        new->prev = NULL;
        new->next = NULL;
        new->val = NULL;
    }
}

void ft_free_env(t_con *env)
{
    t_node *temp;
    t_node *next;

    temp = env->head;
    while (temp)
    {
        next = temp->next;
        free(temp);
        temp = next;
        env->size--;
    }
    free(env);
}

t_node *new_node(char *val)
{
    t_node *new;
    new = (t_node *)malloc(sizeof(t_node));
    if (!new)
    {
        printf("assignment fail!\n");
        exit(1);
    }
    init_con_node(NULL, new, LINKED_NODE);
    new->val = val;
    return (new);
}

t_con *init_env(char **envp)
{
    int idx;
    t_con *env;

    env = (t_con *)malloc(sizeof(t_con));
    idx = 0;
    init_con_node(env, NULL, LINKED_CON);
    while (envp[idx])
    {
        insert_node(env, new_node(envp[idx]), INSERT_TAIL);
        idx++;
    }
    return (env);
}

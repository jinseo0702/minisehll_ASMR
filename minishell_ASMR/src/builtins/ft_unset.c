#include "../../include/minishell.h"

t_node *search_node(t_con *env, char *target)
{
    t_node *current;
    int len;

    len = ft_strlen(target);
	if (len == 0)
		return (NULL);
    current = env->head;
    while (current)
    {
        if (!ft_strncmp(current->val, target, len))
            return (current);     
        current = current->next;
    }
    return (NULL);
}

int is_valid_identifier(const char *str)
{
	int i = 0;

	if (!str || (!ft_isalnum(str[0]) && str[0] != '_'))
		return (0);
	while (str[++i]) {
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

int ft_unset(t_mi *mi, char **two)
{
	int idx = 0;
	
	if (!two || !two[1])
    {
		printf("unset: not enough arguments\n");
		return(-100);
	}
	while (two[++idx])
    {
		if (two[idx][0] == '-')
        {
			printf("unset don't need option");
			idx++;
			return (-100);
		}
		if (!is_valid_identifier(two[idx])) {
			printf("unset: `%s': No search file or directory \n", two[idx]);
			idx++;
			return (-100);
		}
        remove_node(mi->env, search_node(mi->env, two[idx]));
        remove_node(mi->export, search_node(mi->export, two[idx]));
	}
	return (100);
}

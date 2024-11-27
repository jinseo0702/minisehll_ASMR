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

/*void ft_unset(t_con *env, char *target)
{//문법에 맞지 않는 경우는 어떻게 처리 할지 고민입니다. target이 없는z 경우 처리를 어떻게 할까요?
//아직 예외처리를 하지 않았습니다.
//unset의 옵션이 없어야 하고 인자가 이상한게 들어간 경우 어떻게 처리를 해야할지 처리를 하지 않았습니다.
    remove_node(env, search_node(env, target));
}*/
/*
void ft_unset(t_mi *mi, char **two)
{//문법에 맞지 않는 경우는 어떻게 처리 할지 고민입니다. target이 없는 경우 처리를 어떻게 할까요?
//아직 예외처리를 하지 않았습니다.
//unset의 옵션이 없어야 하고 인자가 이상한게 들어간 경우 어떻게 처리를 해야할지 처리를 하지 않았습니다.
    int idx = 0;
    
    while (two[++idx])
    {
        remove_node(mi->env, search_node(mi->env, two[idx]));
        remove_node(mi->export, search_node(mi->export, two[idx]));
    }
}
*/
int is_valid_identifier(const char *str)
{
	int i = 0;

	if (!str || (!ft_isalnum(str[0]) && str[0] != '_')) // 첫 글자는 알파벳 또는 '_'
		return (0);
	while (str[++i]) {
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

void ft_unset(t_mi *mi, char **two)
{
	int idx = 0;
	
	if (!two || !two[1])
    {
		printf("unset: not enough arguments\n");
		return;
	}
	while (two[++idx])
    {
		// 옵션 허용 금지
		if (two[idx][0] == '-')
        {
			printf("unset don't need option");
			idx++;
			return ;
		}
		// 유효하지 않은 변수 이름 검사
		if (!is_valid_identifier(two[idx])) {
			printf("unset: `%s': No search file or directory \n", two[idx]);
			idx++;
			return ;
		}
        remove_node(mi->env, search_node(mi->env, two[idx]));
        remove_node(mi->export, search_node(mi->export, two[idx]));
		// 변수가 존재하지 않더라도 조용히 무시
	}
}

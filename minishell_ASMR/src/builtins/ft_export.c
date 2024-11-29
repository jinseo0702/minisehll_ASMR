#include "../../include/minishell.h"

/*void ft_export(t_con *env, char *val)
{
    insert_node(env, new_node(val), INSERT_TAIL);
}*/
//예외는 아직 고려하지 않고 그냥 노드를 추가하는 함수만 만들었습니다.
//exprot 함수또한 syntex를 지켜야 하기 때문에 이부분에 대한 고민을 해봐야 합니다.
//예를 들면 $표시에 관한 내용이라던가 등등등에 관한 내용을 고려해야 합니다.

void dont_dup(t_mi *mi, char *val)
{
	remove_node(mi->env, search_node(mi->env, val));
	remove_node(mi->export, search_node(mi->export, val));
}

bool is_dup(t_mi *mi, char *val)
{
	t_node *temp;

	temp = search_node(mi->export, val);
	if (temp)
	{
		if(ft_strncmp(temp->val, val, ft_strlen(temp->val)) == '=')
			return (false);
		if (!ft_strncmp(temp->val, val, ft_strlen(val)))
			return (false);
	}
	return(true);
}

bool env_grammar(t_mi *mi, char *val)
{
    /*if(ft_strchr(val, '=') && val[0] != '=')
        printf("%s\n", val);
    else
        return ;*/
    
    char **arry;
    int idx;

    idx = 0;
    if(ft_strchr(val, '=') != NULL)
    {
        arry = ft_split(val, '=');
		dont_dup(mi, arry[0]);
        while (arry[0][idx])
        {
            if (idx == 0 && (ft_isalpha(arry[0][idx]) == 0 && arry[0][idx] != '_'))
            {
                ft_free_two(arry);
                return (false);
            }
            if (ft_isalnum(arry[0][idx]) == 0 && arry[0][idx] != '_')
            {
                ft_free_two(arry);
                return (false);
            }
            idx++;
        }
        ft_free_two(arry);
        return (true);
    }
    return (false);
}

size_t re_two_size(char **two)
{
    size_t siz;

    siz = 0;
    while (two[siz])
        siz++;
    return (siz);
}

void ft_export(t_mi *mi, char **two)//char **two_cmd
{
    t_node *current;
    int idx = 0;
    
    if (re_two_size(two) == 1)
    {
        current = mi->export->head;
        while (current)
        {
            printf("declare -x %s\n", current->val);
            current = current->next;
        }
        return ;
    }
    while (two[++idx])
    {
        if (env_grammar(mi, two[idx]))
        {
            insert_node(mi->env, new_node(ft_strdup(two[idx])), INSERT_TAIL);
            insert_node(mi->export, new_node(ft_strdup(two[idx])), INSERT_TAIL);
        }
        else
		{
			if (!ft_isdigit(two[idx][0]))
			{
				if(is_dup(mi, &two[idx][0]))
            		insert_node(mi->export, new_node(ft_strdup(two[idx])), INSERT_TAIL);
			}
			else
				printf("export: '%s:not a valid identifier\n", two[idx]);
		}
    }
}

//------------------------------

// size_t re_two_size(char **two)
// {
//     size_t siz;

//     siz = 0;
//     while (two[siz])
//         siz++;
//     return (siz);
// }

// char *find_env_value(const char *key, t_mi *mi)
// {
// 	t_node *current = mi->env->head;
// 	size_t key_len = ft_strlen(key);

// 	while (current)
// 	{
// 		// 환경 변수 이름과 key를 비교
// 		if (ft_strncmp(current->val, key, key_len) == 0 && current->val[key_len] == '=')
// 			// '=' 이후 값 반환
// 			return (ft_strchr(current->val, '=') + 1);
// 		current = current->next;
// 	}

// 	// 해당 환경 변수를 찾지 못한 경우
// 	return (NULL);
// }

// // $ 앞부분의 접두사를 추출하는 함수
// char *get_prefix(const char *value)
// {
// 	char *dollar = ft_strchr(value, '$');
// 	size_t prefix_len;
// 	char *prefix;

// 	// $가 없으면 빈 문자열 반환
// 	if (!dollar)
// 		return (ft_strdup(value));

// 	// 접두사 추출
// 	prefix_len = dollar - value;
// 	prefix = (char *)malloc(prefix_len + 1);
// 	if (!prefix)
// 		return (NULL);
// 	ft_strlcpy(prefix, value, prefix_len + 1);

// 	return (prefix);
// }

// // 환경 변수 값을 확장하는 함수
// char *expand_value(const char *value, t_mi *mi)
// {
// 	char *prefix;
// 	char *result = NULL;
// 	char *var_value;
// 	char *dollar = ft_strchr(value, '$');
// 	size_t result_len;

// 	// 접두사 추출
// 	prefix = get_prefix(value);
// 	if (!prefix)
// 		return (NULL);
// 	// $ 이후 변수 이름으로 환경 변수 값 찾기
// 	if (dollar)
// 		var_value = find_env_value(dollar + 1, mi);
// 	else
// 		var_value = NULL;
// 	// 결과 문자열 생성
// 	if (var_value)
// 	{
// 		result_len = ft_strlen(prefix) + ft_strlen(var_value) + 1;
// 		result = (char *)malloc(result_len);
// 		if (result)
// 		{
// 			ft_strlcpy(result, prefix, result_len);
// 			ft_strlcat(result, var_value, result_len);
// 		}
// 	}
// 	else
// 		// 환경 변수 값이 없으면 접두사만 반환
// 		result = ft_strdup(prefix);
// 	free(prefix);
// 	return (result);
// }
// bool env_grammar(char *val)
// {
// 	int idx = 0;
// 	// '='의 위치 확인
// 	while (val[idx] && val[idx] != '=')
// 	{
// 		// 첫 글자는 알파벳 또는 '_'여야 함
// 		if (idx == 0 && (ft_isalpha(val[idx]) == 0 && val[idx] != '_'))
// 			return (false);
// 		// 나머지는 알파벳, 숫자, '_'만 허용
// 		if (ft_isalnum(val[idx]) == 0 && val[idx] != '_')
// 			return (false);
// 		idx++;
// 	}
// 	// '='가 없으면 값 없이 유효한 변수 이름으로 처리
// 	if (val[idx] == '\0')
// 		return (true);
// 	// '=' 이후는 값이므로 별도 검사 없이 유효
// 	return (true);
// }
// // export 함수
// void ft_export(t_mi *mi, char **two)
// {
// 	t_node *current;
// 	int idx;
// 	char *expanded_value;
// 	char	*equal_sign;

// 	idx = 0;
// 	// 인자가 없는 경우: export 리스트 출력
// 	if (re_two_size(two) == 1)
// 	{
// 		current = mi->export->head;
// 		while (current)
// 		{
// 			printf("declare -x %s\n", current->val);
// 			current = current->next;
// 		}
// 		return;
// 	}
// 	// 인자 처리
// 	while (two[++idx])
// 	{
// 		equal_sign = ft_strchr(two[idx], '=');
// 		if (env_grammar(two[idx]))
// 		{
// 			if (equal_sign)
// 			{
// 				expanded_value = expand_value(two[idx], mi);
// 				insert_node(mi->env, new_node(ft_strdup(expanded_value)), INSERT_TAIL);
// 				insert_node(mi->export, new_node(ft_strdup(expanded_value)), INSERT_TAIL);
// 				free(expanded_value);
// 			}
// 			else
// 			{
// 				expanded_value = expand_value(two[idx], mi);
// 				insert_node(mi->export, new_node(ft_strdup(expanded_value)), INSERT_TAIL);
// 				free(expanded_value);
// 			}
// 			continue ;
// 		}
// 		else
// 		{
// 			printf("export: '%s:not a valid identifier\n", two[idx]);
// 			return ;
// 		}
// 	}
// }
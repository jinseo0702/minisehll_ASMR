#include "../../include/minishell.h"
//이부분은 확실하게 파싱의 틀이 잡혀야지 진행이 가능하다.

//안현준이 처리해야할 에러 처리
//2, 출력 실패출력 대상이 표준 출력이 아닌 파일인 경우 쓰기 권한이 없으면 출력이 실패하도록
//3. 입력이 null일 경우를 처리해야한다.
//4. 메모리 부족의 경우


t_echo_option check_option(char *op)
{
    if (*op != '-')
        return (E_NON);
    op++;
    while (*op)
    {
        if (*op != 'n')
            return (E_NON);
        op++;
    }
    return (E_OP);
}

void ft_echo(char **two_cmd) //input == echo -n 
{
    int idx = 0;
    int flag = 0;
    t_echo_option option;

    option = E_NON;
    while (two_cmd[++idx])
    {
        if (!flag && check_option(two_cmd[idx]) == E_OP)
            option = E_OP;
        if (check_option(two_cmd[idx]) == E_NON)
            break;
        flag++;
    }
    while (two_cmd[idx])
    {
        printf ("%s", two_cmd[idx]);
        printf (" ");
        idx++;
    }
    if (option == E_NON)
        printf ("\n");
}

/*
char *expand_env_var(char *str)     //환경변수 처리함수
{
    char    *env;
    char    *value;

    if (str[0] != '$')
    return (str);
    env = str + 1;
    value = getenv(env);
    if (value)
        return (value);
    else
        return("");
}
*/
/*
char *expand_env_var_with_quotes(char *str)
{
    char *result = malloc(1024); // 결과를 저장할 버퍼 (최대 길이 설정)
    int res_idx = 0;             // 결과 문자열의 인덱스
    int i = 0;                   // 입력 문자열의 인덱스

    // 작은따옴표 처리
    if (str[0] == '\'' && str[strlen(str) - 1] == '\'')
    {
        str++;                      // 첫 번째 작은따옴표 건너뜀
        str[strlen(str) - 1] = '\0'; // 마지막 작은따옴표 제거
        return strdup(str);         // 환경변수 확장 없이 그대로 반환
    }

    // 큰따옴표 처리
    if (str[0] == '"' && str[strlen(str) - 1] == '"')
    {
        str++;                      // 첫 번째 큰따옴표 건너뜀
        str[strlen(str) - 1] = '\0'; // 마지막 큰따옴표 제거
    }

    // 환경 변수 처리 및 복사
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1]) // 환경 변수 시작
        {
            i++; // '$'를 건너뜀
            int start = i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) // 변수 이름 추출
                i++;
            char *env_name = ft_strndup(&str[start], i - start); // 환경 변수 이름 추출
            char *env_value = getenv(env_name);               // 환경 변수 값 가져오기
            free(env_name);

            if (env_value) // 환경 변수 값이 존재하면 결과에 추가
            {
                int j = 0;
                while (env_value[j])
                    result[res_idx++] = env_value[j++];
            }
        }
        else // 일반 문자 복사
        {
            result[res_idx++] = str[i++];
        }
    }
    result[res_idx] = '\0'; // 문자열 종료
    return result;
}
*/

// char *handle_single_quotes(char *str)
// {
//     char *result;

//     if (str[0] == '\'' && str[strlen(str) - 1] == '\'')
//     {
//         str++;                      // 첫 번째 작은따옴표 건너뜀
//         str[ft_strlen(str) - 1] = '\0'; // 마지막 작은따옴표 제거
//         result = ft_strdup(str);       // 환경변수 확장 없이 그대로 반환
//         return (result);
//     }
//     return (NULL); // 작은따옴표가 없으면 NULL 반환
// }


// char *handle_double_quotes(char *str)
// {
//     if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
//     {
//         str++;                      // 첫 번째 큰따옴표 건너뜀
//         str[ft_strlen(str) - 1] = '\0'; // 마지막 큰따옴표 제거
//     }
//     return (str); // 큰따옴표가 없으면 원본 문자열 반환
// }

// void expand_env_variable(char *str, char *result, int *res_idx)
// {
//     int i;
//     int start;
//     char *env_name;
//     char *env_value;
//     int j;

//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == '$' && str[i + 1]) // 환경 변수 시작
//         {
//             i++; // '$'를 건너뜀
//             start = i;
//             while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) // 변수 이름 추출
//                 i++;
//             env_name = ft_strndup(&str[start], i - start); // 환경 변수 이름 추출
//             env_value = getenv(env_name);              // 환경 변수 값 가져오기
//             free(env_name);

//             if (env_value) // 환경 변수 값이 존재하면 결과에 추가
//             {
//                 j = 0;
//                 while (env_value[j])
//                     result[(*res_idx)++] = env_value[j++];
//             }
//         }
//         else // 일반 문자 복사
//         {
//             result[(*res_idx)++] = str[i++];
//         }
//     }
// }


// char *expand_env_var_with_quotes(char *str)
// {
//     char *result;
//     char *single_quoted;
//     int res_idx;

//     result = malloc(1024); // 결과를 저장할 버퍼 (최대 길이 설정)
//     res_idx = 0;

//     // 작은따옴표 처리
//     single_quoted = handle_single_quotes(str);
//     if (single_quoted)
//         return single_quoted; // 작은따옴표 안의 문자열 반환

//     // 큰따옴표 처리
//     str = handle_double_quotes(str);

//     // 환경 변수 확장 및 복사
//     expand_env_variable(str, result, &res_idx);

//     result[res_idx] = '\0'; // 문자열 종료
//     return (result);
// }



// t_echo_option check_option(char *op)
// {
// 	if (*op != '-')
// 		return (E_NON);
// 	op++;
// 	while (*op) {
// 		if (*op != 'n')
// 			return (E_NON);
// 		op++;
// 	}
// 	return (E_OP);
// }

/*
void ft_echo(char **two_cmd) // input == echo -n
{
	int idx = 0;
	int flag = 0;
    char    *output;
	t_echo_option option = E_NON;

	if (!two_cmd || !two_cmd[0])
    { 
		printf("\n");
		return;
	}
	// 옵션 처리
	while (two_cmd[++idx])
    {
		if (!flag && check_option(two_cmd[idx]) == E_OP)
        {
			option = E_OP; // -n 옵션 활성화
			flag++;
			continue;
		}
		if (check_option(two_cmd[idx]) == E_NON)
			break;
		flag++;
	}
	// 문자열 출력
	while (two_cmd[idx])
    {
        output = expand_env_var(two_cmd[idx]);
        printf("%s", output);
		idx++;
		if (two_cmd[idx]) // 마지막 단어 뒤 공백 제거
			printf(" "); // 기존 코드에서는 항상 공백 출력
	}
	// -n 옵션에 따른 개행 처리
	if (option == E_NON)
		printf("\n");
}
*/

// t_echo_option check_option(char *op)
// {
// 	if (*op != '-')
// 		return (E_NON);
// 	op++;
// 	while (*op) {
// 		if (*op != 'n')
// 			return (E_NON);
// 		op++;
// 	}
// 	return (E_OP);
// }

int handle_single_quotes(char *str, char *result, int *i, int *res_idx)
{
    (*i)++; // 첫 번째 작은따옴표 건너뜀
    while (str[*i] && str[*i] != '\'') // 작은따옴표 안의 내용 복사
        result[(*res_idx)++] = str[(*i)++];
    if (str[*i] == '\'') // 닫는 작은따옴표 건너뜀
        (*i)++;
    return (1); // 처리 완료
}

int handle_double_quotes(char *str, char *result, int *i, int *res_idx)
{
    int start;
    char *env_name;
    char *env_value;
    int j;

    start = 0;
    env_name = NULL;
    env_value = NULL;
    j = 0;

    (*i)++; // 첫 번째 큰따옴표 건너뜀
    while (str[*i] && str[*i] != '"')
    {
        if (str[*i] == '$') // 환경 변수 확장
        {
            start = ++(*i);
            while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_')) // 변수 이름 추출
                (*i)++;
            env_name = ft_strndup(&str[start], *i - start);
            env_value = getenv(env_name);
            free(env_name);

            if (env_value)
            {
                j = 0;
                while (env_value[j])
                    result[(*res_idx)++] = env_value[j++];
            }
        }
        else // 일반 문자 복사
        {
            result[(*res_idx)++] = str[(*i)++];
        }
    }
    if (str[*i] == '"') // 닫는 큰따옴표 건너뜀
        (*i)++;
    return (1); // 처리 완료
}

int handle_env_variable(char *str, char *result, int *i, int *res_idx)
{
    int start;
    char *env_name;
    char *env_value;
    int j;

    start = 0;
    env_name = NULL;
    env_value = NULL;
    j = 0;

    if (str[*i] == '$' && str[*i + 1])
    {
        start = ++(*i);
        while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_')) // 변수 이름 추출
            (*i)++;
        env_name = ft_strndup(&str[start], *i - start);
        env_value = getenv(env_name);
        free(env_name);

        if (env_value)
        {
            j = 0;
            while (env_value[j])
                result[(*res_idx)++] = env_value[j++];
        }
        return (1); // 처리 완료
    }
    return (0); // 환경 변수가 아니면 처리하지 않음
}

char *expand_env_var_with_quotes(char *str)
{
    char *result;
    int res_idx;
    int i;

    result = malloc(1024); // 결과를 저장할 버퍼
    res_idx = 0;
    i = 0;

    while (str[i])
    {
        if (str[i] == '\'') // 작은따옴표 처리
        {
            handle_single_quotes(str, result, &i, &res_idx);
            continue;
        }
        if (str[i] == '"') // 큰따옴표 처리
        {
            handle_double_quotes(str, result, &i, &res_idx);
            continue;
        }
        if (str[i] == '$') // 환경 변수 처리
        {
            if (handle_env_variable(str, result, &i, &res_idx))
                continue;
        }
        // 일반 문자 복사
        result[res_idx++] = str[i++];
    }

    result[res_idx] = '\0'; // 문자열 종료
    return (result);
}

// void ft_echo(char **two_cmd) // input == echo -n
// {
//     int idx = 0;
//     int flag = 0;
//     char *output;
//     t_echo_option option = E_NON;

//     if (!two_cmd || !two_cmd[0])
//     {
//         printf("\n");
//         return;
//     }
//     // 옵션 처리
//     while (two_cmd[++idx])
//     {
//         if (!flag && check_option(two_cmd[idx]) == E_OP)
//         {
//             option = E_OP; // -n 옵션 활성화
//             flag++;
//             continue;
//         }
//         if (check_option(two_cmd[idx]) == E_NON)
//             break;
//         flag++;
//     }
//     // 문자열 출력
//     while (two_cmd[idx])
//     {
//         output = expand_env_var_with_quotes(two_cmd[idx]); // 큰따옴표 처리 포함
//         printf("%s", output);
//         free(output); // 동적 메모리 해제
//         idx++;
//         if (two_cmd[idx]) // 마지막 단어 뒤 공백 제거
//           printf(" ");
//     }
//     // -n 옵션에 따른 개행 처리
//     if (option == E_NON)
//         printf("\n");
// }

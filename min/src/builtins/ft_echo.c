#include "../../include/minishell.h"
//이부분은 확실하게 파싱의 틀이 잡혀야지 진행이 가능하다.

//안현준이 처리해야할 에러 처리
//2, 출력 실패출력 대상이 표준 출력이 아닌 파일인 경우 쓰기 권한이 없으면 출력이 실패하도록
//3. 입력이 null일 경우를 처리해야한다.
//4. 메모리 부족의 경우

/*
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

void ft_echo(t_mi *mi, char **two_cmd) //input == echo -n 
{
    (void)mi;//$처리하기 아직 yet
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
*/

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

t_echo_option check_option(char *op)
{
	if (*op != '-')
		return (E_NON);
	op++;
	while (*op) {
		if (*op != 'n')
			return (E_NON);
		op++;
	}
	return (E_OP);
}
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

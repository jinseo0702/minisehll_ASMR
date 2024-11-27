#include "../../include/minishell.h"

/*void ft_cd(const char *input)
{
    char *str = calloc(1, 400);
    str = readline("root");//수정해야합니다.
    // printf("%s !!!! \n", str);
    //~, - 등의 경로또한 처리를 해줘야합니다.
    if (chdir(str) == -1)
    {
        //errno로 error를 처리하는 부분을 생각을 해줘야합니다.
        printf("%serror !!!! \n", str);
        return ;
    }
    free(str);// 수정해야 합니다.
}*/

/*
void ft_cd(char **two_cmd)
{
    if (chdir(two_cmd[1]) == -1)
    {
        printf("%serror !!!! \n", two_cmd[1]);
        return ;
    }
}
*/
/*
char *expand_env_var_for_cd(char *str)
{
    char *result;
    int res_idx;
    int i;
    int start;
    char *env_name;
    char *env_value;

    result = malloc(1024); // 결과를 저장할 버퍼
    res_idx = 0;
    i = 0;

    while (str[i])
    {
        // 작은따옴표 처리
        if (str[i] == '\'' && strchr(&str[i + 1], '\''))
        {
            i++; // 첫 번째 작은따옴표 건너뜀
            while (str[i] && str[i] != '\'') // 작은따옴표 안의 문자열 복사
                result[res_idx++] = str[i++];
            i++; // 닫는 작은따옴표 건너뜀
        }
        // 큰따옴표 처리
        else if (str[i] == '"' && strchr(&str[i + 1], '"'))
        {
            i++; // 첫 번째 큰따옴표 건너뜀
            while (str[i] && str[i] != '"') // 큰따옴표 안의 문자열 복사
            {
                if (str[i] == '$' && str[i + 1]) // 환경 변수 시작
                {
                    i++; // '$'를 건너뜀
                    start = i;
                    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) // 변수 이름 추출
                        i++;
                    env_name = strndup(&str[start], i - start); // 환경 변수 이름 추출
                    env_value = getenv(env_name);              // 환경 변수 값 가져오기
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
            i++; // 닫는 큰따옴표 건너뜀
        }
        // 환경 변수 처리
        else if (str[i] == '$' && str[i + 1])
        {
            i++; // '$'를 건너뜀
            start = i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) // 변수 이름 추출
                i++;
            env_name = strndup(&str[start], i - start); // 환경 변수 이름 추출
            env_value = getenv(env_name);              // 환경 변수 값 가져오기
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

/*
void ft_cd(char **two_cmd)
{
	if (chdir(two_cmd[1]) == -1)
    {
		// chdir 실패 시, errno를 활용해 에러 원인을 출력
		if (errno == ENOENT)        //경로가 존재하지 않음
			printf("cd: %s: No such file or directory\n", two_cmd[1]);
		 else if (errno == EACCES)  //디렉토리에 대한 권한이 없음
			printf("cd: %s: Permission denied\n", two_cmd[1]);
		else if (errno == ENOTDIR)  //경로 중 일부가 디렉토리가 아님
			printf("cd: %s: Not a directory\n", two_cmd[1]);
		else
			printf("cd: %s: Error: %s\n", two_cmd[1], strerror(errno));
    }
		return;
}
*/






void ft_cd(char **two_cmd)
{
    char    *home;
    char *path;
    char *expanded_path;
    char *tmp;
    char    *prev_dir;

    if (!two_cmd[1] || ft_strlen(two_cmd[1]) == 0) // 인자가 없는 경우
    {
        path = getenv("HOME"); // $HOME 환경변수 가져오기
        if (!path)
        {
            printf("cd: HOME not set\n");
            return;
        }
    }
    else
        path = two_cmd[1]; // 사용자가 입력한 경로
    if (path[0] == '~')
    {
        home = getenv("HOME");
        if (home)
        {
            if (path[1] == '/')
            {
                tmp = path;
                path = ft_strjoin(home, path + 1);
                free(tmp);
            }
            else if (path[1] == '\0')
            {
                free(path);
                path = ft_strdup(home);
            }
        }
    }
    prev_dir = getcwd(NULL, 0);
    if (!prev_dir)
    {
        printf ("cd: Unable to save current directory");
        return ;
    }
        
    // 경로 확장
    expanded_path = expand_env_var_with_quotes(path);
    // chdir 호출
    if (chdir(expanded_path) == -1)
    {
        // chdir 실패 시, errno를 활용해 에러 원인을 출력
        if (errno == ENOENT)        // 경로가 존재하지 않음
            printf("cd: %s: No such file or directory\n", expanded_path);
        else if (errno == EACCES)  // 디렉토리에 대한 권한이 없음
            printf("cd: %s: Permission denied\n", expanded_path);
        else if (errno == ENOTDIR) // 경로 중 일부가 디렉토리가 아님
            printf("cd: %s: Not a directory\n", expanded_path);
        else
            printf("cd: %s: Error: %s\n", expanded_path, strerror(errno));
        if (chdir(prev_dir) == -1)//디렉토리 복구
        printf ("cd: Failed to return to previous directory: %s\n", strerror(errno));
    }
    free(prev_dir);
    free(expanded_path); // 동적 메모리 해제
}



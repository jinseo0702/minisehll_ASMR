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

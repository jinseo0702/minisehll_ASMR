#include "../../include/minishell.h"
/*
//PATH_MAX는 4096로 제한되어 있음.
void ft_pwd(void)
{
    int idx;
    char buf[4100];

    idx = -1;
    while (++idx < 4100)
        buf[idx] = 0;
    if(getcwd(buf, sizeof(buf)) == NULL)
        printf("%s\n", strerror(errno));
    else
        printf("%s\n", buf);
}
//pwd함수는 옵션이 있으면 안됩니다. 이부분은 파싱의 틀이 만들어져야지 고칠 수 있습니다.
*/
void ft_pwd(char **two_cmd)
{
	char buf[4100];
    int     idx;

    idx = 0;
    if (two_cmd[++idx])
    {
        printf("pwd don't need any option \n");
        return ;
    }
	ft_memset(buf, 0, sizeof(buf));
	if (getcwd(buf, sizeof(buf)) == NULL)
    {
		if (errno == ENOMEM)
			printf("pwd: Memory allocation failed\n");
		else if (errno == EACCES)
			printf("pwd: Permission denied\n");
		else if (errno == ENAMETOOLONG)
			printf("pwd: Path is too long\n");
		else
			printf("pwd: Error retrieving current directory: %s\n", strerror(errno));
	}
    else
    {
		printf("%s\n", buf);
	}
}
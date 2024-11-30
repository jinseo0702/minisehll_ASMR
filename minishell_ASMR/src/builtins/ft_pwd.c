#include "../../include/minishell.h"

int ft_pwd(char **two_cmd)
{
	char buf[4100];
    int     idx;

    idx = 0;
    if (two_cmd[++idx])
    {
        printf("pwd don't need any option \n");
        return (-100);
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
        return (-100);
	}
    else
    {
		printf("%s\n", buf);
	}
    return (100);
}
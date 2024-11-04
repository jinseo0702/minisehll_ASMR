#include "../../include/minishell.h"

int main()
{
	char buf[256];
	getcwd(buf, sizeof(buf));
	printf("%s \n", buf);
	//printf("%s \n", str);
	char *str;
	str = readline("root");
	chdir(str);
	char buf2[256];
	getcwd(buf2, sizeof(buf2));
	printf("%s \n", buf2);
	free(str);
	return (0);
}
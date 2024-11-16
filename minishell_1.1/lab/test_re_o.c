#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void print_progress() 
{
	printf("작업 진행 중...\n");
	printf("[===>    ] 30%% 완료\n");
	rl_on_new_line(); // 이 줄을 주석 처리하여 문제 발생
				// 
}

int main() {
	    char *input;
		while ((input = readline("~$ ")) != NULL)
		{
			add_history(input);
			if (strcmp(input, "ls -pdkd") == 0) 
			{
				rl_on_new_line(); // 이 줄을 주석 처리하여 문제 발생
				rl_redisplay();
				rl_on_new_line(); // 이 줄을 주석 처리하여 문제 발생
				//rl_clear_history();
				printf("is not command!\n");
				rl_redisplay();
			}
			if (strcmp(input, "clear") == 0) 
			{
				rl_clear_history();
			}
			if (strcmp(input, "^C") == 0) 
			{
				printf("^C\n");
			}
			if (strcmp(input, "progress") == 0) 
			{
				print_progress();
			}
			else if (strcmp(input, "exit") == 0) 
			{
				free(input);
				break;
			}
			char **split = ft_split(input, '|');
			int i = 0;
			while (split[i])
			{
				printf("%s \n", split[i]);
				i++;
			}
			printf("%s \n", input);
			free(input);		    
		}
		    return 0;
			
}

// 컴파일: gcc -o readline_error_example readline_error_example.c -lreadline
// // 실행: ./readline_error_example

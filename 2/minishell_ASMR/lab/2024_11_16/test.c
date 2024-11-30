#include "../../include/minishell.h"

void check_pipe(char *input)
{
    int s_q = 0;
    int d_q = 0;
    int cnt = 0;
	char *temp = input;
	char *temp2;
    while (*temp)
    {
        if (*temp == '\"')
            d_q++;
        else if (*temp == '\'')
            s_q++;
        if (d_q == 2)
            d_q = 0;
        if (s_q == 2)
            s_q = 0;
        if ((!d_q && !s_q) && *temp == '|')
		{
			temp2 = ft_strndup(input, ft_strchr_len(input, *temp));
			temp++;
			input = temp;
			printf("%s\n", temp2);
			free(temp2);
            cnt++;
			continue;
		}
        temp++;
    }
//    printf("%d\n", cnt);
}

int main(void)
{
    char *input;

    input = readline("~> ");
    check_pipe(input);
    // char **str = ft_split_str(input, "\"\'");
    int i = 0;
    // while (str[i])
    // {
    //     printf("%s\n", str[i]);
    //     i++;
    // }
    // ft_free_two(str);
    free(input);
    return(0);
}

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

void ft_cd(const char *input, t_con *test)
{
    test->head = test->head->next;
    if (chdir(test->head->val) == -1)
    {
        printf("%serror !!!! \n", test->head->val);
        return ;
    }
}
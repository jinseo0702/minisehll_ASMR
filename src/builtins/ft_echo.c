#include "../../include/minishell.h"
//이부분은 확실하게 파싱의 틀이 잡혀야지 진행이 가능하다.

typedef enum echo_option 
{
    ECHO_NONE,
    ECHO_N,
}   t_echo_option;

bool ft_isspace(int c)
{
    if (ft_strchr(" \f\n\r\t\v", c) != c)
        return (true);
    else
        return (false);
}

static int check_option(char *op)
{
    int flag;
    static int idx;

    flag = ECHO_N;
    while (op[idx] || ft_isspace(*op))
    {
        if (op[0] == '-')
        {
            idx++;
            while (/* condition */)
            {
                /* code */
            }
        }
        op++;
    }
    
}

void ft_echo(char *input) //input == echo -n 
{
    char *cpy;
    int op;

    cpy = input;
    op = check_option(cpy);
    if (op == ECHO_NONE)
        printf("%s\n", cpy);
    else if (op == ECHO_N)
        printf("%s", cpy);
}

int main()
{
    ft_echo("-nnn Hello Wrold");
    return (0);
}
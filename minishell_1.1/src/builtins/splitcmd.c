#include "../../include/minishell.h"
//파싱이 완료되기전에 test하기 위해 만들었습니다.
t_con *miniparse(char *input)
{
    t_con *cmd = malloc(sizeof(t_con));
    char **split = ft_split(input, ' ');
    int idx = 0;

    init_con_node(cmd, NULL, LINKED_CON);
    while (split[idx])
    {
        insert_node(cmd, new_node(split[idx]), INSERT_TAIL);
        idx++;
    }
    return (cmd);
}
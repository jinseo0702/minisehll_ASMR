#include "../../include/minishell.h"

void ft_free_con(t_con *con)
{
    t_node *temp;
    t_node *next;

    temp = con->head;
    while (temp)
    {
        next = temp->next;
        free(temp);
        temp = next;
        con->size--;
    }
    con->head = NULL;
    con->tail = NULL;
}

int is_valid_number(const char *str) {
    int i = 0;
    if (str[i] == '-')
        i++;
    while (str[i]) {
        if (!isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}
void ft_exit(t_mi *mi, char **two_cmd) {
    long long exit_code = 0;
    // 인자가 없는 경우: 메모리 해제 후 종료
    if (!two_cmd || !two_cmd[1]) {
        printf("exit\n");
        if (mi->env)
            ft_free_con(mi->env);
        if (mi->export)
            ft_free_con(mi->export);
        if (mi->head)
            ft_free_pcon(mi->head);
        exit(0);
    }
    // 숫자인지 아닌지 유효성 검사
    if (!is_valid_number(two_cmd[1])) {
        printf("exit: %s: numeric argument required\n", two_cmd[1]);
        exit(2); // 비정상 종료
    }
    if (two_cmd[2]) {
        printf("exit: too many arguments\n");
        return; // 종료하지 않고 명령어만 무시
    }
    exit_code = ft_atoi_longlong(two_cmd[1]);
    if (exit_code > 9223372036854775807)    //long long 최댓값 처리.
    {
        printf("exit: %s: numeric argument required\n", two_cmd[1]);
        exit (2);
    }
    // 종료 코드 설정
    //exit_code = ft_atoi_longlong(two_cmd[1]) % 256;
    // 메모리 해제
    if (mi->env)
        ft_free_con(mi->env);
    if (mi->export)
        ft_free_con(mi->export);
    if (mi->head)
        ft_free_pcon(mi->head);
    printf("exit\n");
    exit(exit_code);
}
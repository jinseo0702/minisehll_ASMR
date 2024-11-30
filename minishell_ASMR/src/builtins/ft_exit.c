#include "../../include/minishell.h"

/*
void ft_exit(t_mi *mi, char **two_cmd)
{
    // 사용하지 않는 매개변수 처리
    (void)two_cmd;

    // 환경 변수 해제
    if (mi->env)
        ft_free_con(mi->env);
    if (mi->export)
        ft_free_con(mi->export);
    // 명령어 리스트 해제
    if (mi->head)
        ft_free_pcon(mi->head);

    printf("end shell\n"); // 테스트용 출력
    exit(0);
}
*/

//==========================================================
// 현재까지 exit 함수를 처리하기 위해 남은 예외상활
//1. 파이프 상태 처리, mi에 exit_flg를 만들어서 파이프가 있는 경우 exit 명령어가 무시되도록 만드는 코드가 필요함
//2. 할당된 메모리가 잘 해제되는지를 확인해야함.

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

// 숫자 유효성 검사 함수
int is_valid_number(const char *str) {
    int i = 0;
    // 음수 기호 허용
    if (str[i] == '-')
        i++;
    // 숫자가 아니면 false
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
    // 여러 인자 처리
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
    // 종료
    printf("exit\n");
    exit(exit_code);
}
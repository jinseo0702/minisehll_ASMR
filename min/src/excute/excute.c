#include "../../include/minishell.h"

char **merge_env(t_mi *mi)
{
    char **exe_env;
    int idx;
    t_node *current;

    idx = -1;
    exe_env = (char **)malloc(sizeof(char *) * (mi->env->size + 1));
    if (exe_env == NULL)
            exit(1);//할당실패시 어떻게 할지 고민입니다.
    current = mi->env->head;
    while (current)
    {
        exe_env[++idx] = ft_strdup(current->val);
        current = current->next;
    }
    exe_env[mi->env->size] = NULL;
    return (exe_env);
}

char **merge_option(t_mi *mi)//option 리스트로 교체할 예정 입니다.
{
    char **exe_option;
    int idx;
    int size;
    t_pan *current;

    idx = -1;
    size = check_size(mi);
    exe_option = (char **)malloc(sizeof(char *) * (size + 1));
    if (exe_option == NULL)
            exit(1);//할당실패시 어떻게 할지 고민입니다.
    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        // printf("size == %s \n", current->val);
        exe_option[++idx] = ft_strdup(current->val);
        remove_pan(mi->head, current);
        current = mi->head->head;
    }
    if (current && current->type == T_PIPE)
    {
        remove_pan(mi->head, current);
        mi->pcnt--;
    }
    exe_option[size] = NULL;
    return (exe_option);
}

void printf_two(char **str)
{
    int idx = -1;
    while (str[++idx])
        printf("%s \n", str[idx]);
}

void exe_cmd(t_mi *mi)
{
    char **two_env;
    char **two_cmd;
    char *path;

    find_redi(mi);
    two_env = merge_env(mi);
    two_cmd = merge_option(mi);
    path = return_path(mi, two_cmd[0]);
    excute_cmd(mi, check_builtins(two_cmd[0]), two_cmd);
    if (check_builtins(two_cmd[0]) == BUILT_NOT)
    {
        if (!real_execute(two_env, two_cmd, path))
        {
            perror(two_cmd[0]);
            free_two(two_env);
            free_two(two_cmd);
            free(path);//추후 에러는 상의하자.
            // printf("ERORR\n");//에러처리 어케 할래??
            exit(1);//이상한 명령어가 들어오면 종료를 합니다.
        }
    }
    free_two(two_env);
    free_two(two_cmd);
    free(path);//추후 에러는 상의하자.
}

char *real_execute(char **env, char **cmd, char *path)
{
    if (execve(path, cmd, env) == -1)//두번째 인자랑 세번째 인자는 있다고 가정 합니다.
    {
        //error처리를 해야 합니다/
        return (NULL);
    }
    return (NULL);
}

int check_size(t_mi *mi)
{
    t_pan *current;
    int cnt = 0;

    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        cnt++;
        current = current->next;
    }
    return (cnt);
}

int check_fork(t_mi *mi)
{
    t_pan *current;
    char *path;

    current = mi->head->head;
    while (current)
    {
        if (current->type == T_REDIRECTION)
        {
            current = current->next;
            current = current->next;
        }
        else
        {
            break;
        }
    }
    if (check_builtins(current->val) == BUILT_NOT)
        return (0);
    return (1);
}

int not_fork(t_mi *mi)
{
    int std_i;
    int std_o;

    std_i = dup(0);
    std_o = dup(1);
    if (std_i == -1 || std_o == -1)//표준 입출력중 하나가 에러가 난다면?
        return (-1);//error 처리를 해야한다.
    exe_cmd(mi);
    if (dup2(std_i, 0) == -1 || dup2(std_o, 1) == -1)
        return (-1);//error 처리를 해야한다.
    close(std_i);
    close(std_o);
    return (1);
}

void proc_fork(t_mi *mi)
{//<file1 cat -e | ls -al | C | D
    int pid;
    int rf = -1;

    if (mi->pcnt == 0)
    {
        if (check_fork(mi) == 1)
        {
            if (not_fork(mi) == -1)
                printf("error 처리하기\n");
            return ;
        }
    }
    pid = fork();
    if (pid == -1)
        exit(1);//error입니다.
    else if (pid == 0)
    {//MASTER
        proc_fork_2(mi, rf + 1);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        printf("Hello World\n");//MASTER
    }
}

void delete_node(t_mi *mi)
{
    t_pan *current;

    current = mi->head->head;
    while (current && current->type != T_PIPE)
    {
        remove_pan(mi->head, current);
        current = mi->head->head;
    }
    if (current->type == T_PIPE)
        remove_pan(mi->head, current);
    return ;
}

void proc_fork_2(t_mi *mi, int rf)
{//<file1 cat -e | ls -al | C | D
    int pid = -1000;//이것도 고려해야 할 점 입니다.

    if (rf < mi->pcnt)
    {
        if(pipe(mi->fd) == -1)
            exit(1);//error처리하기.
        pid = fork();
    }
    if (pid == -1)
        exit(1);//error입니다.
    if (pid == 0)
    {
        close(mi->fd[1]);
        if (dup2(mi->fd[0], 0) == -1)
                return ;//error 처리를 해야한다
            close(mi->fd[0]);//
        delete_node(mi);
        proc_fork_2(mi, rf + 1);
    }
    else
    {
        if (rf < mi->pcnt)
            waitpid(pid, NULL, WNOHANG);
        if (rf < mi->pcnt)
        {
            if (dup2(mi->fd[1], 1) == -1)
                return ;//error 처리를 해야한다.
            //close(mi->fd[0]);//
            close(mi->fd[1]);//
        }
        if (mi->pcnt > 0)//처음일 때는 안쓰는 pipe중 입력을 닫아줘야 합니다.
            close(mi->fd[0]);
        if (mi->pcnt > 0 && rf == mi->pcnt)//마지막인경우 사용안하는 pipe중 출력을 닫아 줘야합니다.
            close(mi->fd[1]);
        exe_cmd(mi);
    }
    exit(pid);
}


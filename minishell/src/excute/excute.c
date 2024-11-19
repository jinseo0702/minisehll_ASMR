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

    // print_pcon(mi->head);//del
    find_redi(mi);
    // printf("out \n");//del
    // print_pcon(mi->head);//del
    two_env = merge_env(mi);
    two_cmd = merge_option(mi);
    path = return_path(mi, two_cmd[0]);
    excute_cmd(mi, check_builtins(path), two_cmd);
    if (!real_execute(two_env, two_cmd, path))
    {
        free_two(two_env);
        free_two(two_cmd);
        free(path);//추후 에러는 상의하자.
    }
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

void proc_fork(t_mi *mi)
{//<file1 cat -e | ls -al | C | D
    int pid;
    int rf = -1;

    pid = fork();
    if (pid == -1)
        exit(1);//error입니다.
    if (pid == 0)
    {//MASTER
        proc_fork_2(mi, rf + 1);
    }
    else
    {
        wait(&pid);
        printf("Hello World\n");//MASTER
    }
}

void proc_fork_2(t_mi *mi, int rf)
{//<file1 cat -e | ls -al | C | D
    int pid = -1000;

    if (rf < mi->pcnt)
        pid = fork();
    if (pid == -1)
        exit(1);//error입니다.
    if (pid == 0)
    {
        if(pipe(mi->fd) == -1)
            exit(1);//error처리하기.
        proc_fork_2(mi, rf + 1);
    }
    else
    {
        exe_cmd(mi);
    }
        return ;
}



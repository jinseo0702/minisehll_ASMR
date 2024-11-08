#include "../../include/minishell.h"

char **merge_env(t_con *env)
{
    char **exe_env;
    int idx;
    t_node *current;

    idx = -1;
    exe_env = (char **)malloc(sizeof(char *) * (env->size + 1));
    if (exe_env == NULL)
            exit(1);//할당실패시 어떻게 할지 고민입니다.
    current = env->head;
    while (current)
    {
        exe_env[++idx] = ft_strdup(current->val);
        current = current->next;
    }
    exe_env[env->size] = NULL;
    return (exe_env);
}

char **merge_option(t_con *env)//option 리스트로 교체할 예정 입니다.
{
    char **exe_option;
    int idx;
    t_node *current;

    idx = -1;
    exe_option = (char **)malloc(sizeof(char *) * (env->size + 1));
    if (exe_option == NULL)
            exit(1);//할당실패시 어떻게 할지 고민입니다.
    current = env->head;
    while (current)
    {
        exe_option[++idx] = ft_strdup(current->val);
        current = current->next;
    }
    exe_option[env->size] = NULL;
    return (exe_option);
}

void exe_cmd(t_con *env, t_con *test)
{
    char **two_env;
    char **two_cmd;
    char *path;

    two_env = merge_env(env);
    two_cmd = merge_option(test);
    path = return_path(env, test->head->val);
    proc_fork(two_env, two_cmd, path);
    free_two(two_env);
    free_two(two_cmd);
    free(path);
}

int proc_fork(char **env, char **cmd, char *path)
{
    int pid;

    pid = fork();
    waitpid(pid, 0, WNOHANG);
    if (pid == -1)
        exit(1);//error입니다.
    if (pid == 0)
    {
        if (execve(path, cmd, env) == -1)//두번째 인자랑 세번째 인자는 있다고 가정 합니다.
        {
            //error처리를 해야 합니다/
            exit(1);
        }
    }
}
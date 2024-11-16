#include "../../include/minishell.h"

void init_mi(t_mi *mi, char **envp)
{
    mi->env = init_env(envp);//해제하는 부분을 생각 안했다.
    mi->export = init_env(envp);//해제하는 부분을 생각 안했다.
    mi->syntaxs = NULL;
    mi->input = NULL;
    pipe(mi->fd);//error 처리 하자...
}

int main(int argc, char **argv, char **envp)
{
    t_mi mi;

    init_mi(&mi, envp);
    prompt(&mi);
    return (0);
}
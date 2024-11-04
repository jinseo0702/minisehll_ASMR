#include "../../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_con env;

    init_env(&env, envp);
    prompt(&env);
    return (0);
}
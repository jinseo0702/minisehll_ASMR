#include "../../include/minishell.h"

//들어가야 하는 함수 목록 dup2  open 
typedef enum
{
    T_DLESS,    //  <<
    T_DGREAT,   //  >>
    T_LESS,     //  <
    T_GREAT     //  >
}   T_RDT;

int open_file(char *file, T_RDT re)
 {
    int fd;

    if (re == T_LESS)
        fd = open(file, O_RDONLY, 0644);
    else if (re == T_GREAT)
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (re == T_DGREAT)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        printf("error !!\n");
    return (fd);
}
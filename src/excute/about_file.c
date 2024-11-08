#include "../../include/minishell.h"

//들어가야 하는 함수 목록 dup2  open 
typedef enum
{
    T_DLESS,    //  <<
    T_DGREAT,   //  >>
    T_LESS,     //  <
    T_GREAT     //  >
}   T_RDT;

void ft_change_fd()
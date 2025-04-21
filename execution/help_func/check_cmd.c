#include "../../minishell.h"

void    check_cmd(t_node *args, char **env)
{
    if(!args)
        return ;
    if(check_builtins_cmd(args, env) == 0)
        printf("extrnal_cmd !!\n");
}

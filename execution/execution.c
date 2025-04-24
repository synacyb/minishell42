#include "../minishell.h"

void    exeuction_cmds(t_node *args, t_list *env)
{
    if(args->args[0] == NULL) // if the user send a empty string !
        return ;
    check_cmd(args, env);
}

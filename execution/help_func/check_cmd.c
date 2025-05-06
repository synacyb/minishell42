#include "../../minishell.h"

void    check_cmd(t_node *args, t_list **env)
{
    if(check_builtins_cmd(args, env) == 0)
        external_cmd(args, *env);
}

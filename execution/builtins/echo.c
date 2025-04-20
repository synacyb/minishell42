#include "../../minishell.h"

void    ft_echo(t_node   *cmd)
{
    if (!cmd || !cmd->args[0])
    {
        // ft_free_args();
        return ;
    }
    if(ft_strcmp(cmd->args[1], "-n") == 0)
        ft_putstr_fd(cmd->args[2], 1);
    
    else
        ft_putendl_fd(cmd->args[1], 1);
}
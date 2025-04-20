#include "../../minishell.h"

void    check_cmd(t_node *args)
{
    if (ft_strcmp(args->cmd, "echo") == 0)
        ft_echo(args);
    if(ft_strcmp(args->cmd, "pwd"))
        ft_pwd(args);
}

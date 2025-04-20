#include "../minishell.h"

void    check_cmd(t_cmd *args)
{
    if (ft_strcmp(args->cmd, "echo") == 0)
        ft_echo(args);
}

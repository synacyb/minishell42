#include "../minishell.h"

void    ft_echo(t_cmd   *args)
{
    if (!args || !args->args[0])
    {
        // ft_free_args();
        return ;
    }
    if(ft_strcmp(args->args[1], "-n") == 0)
        ft_putstr_fd(args->args[2], 1);
    
    else
        ft_putendl_fd(args->args[1], 1);
}
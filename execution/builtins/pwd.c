#include "../../minishell.h"

void    ft_pwd(t_node   *cmd)
{
    if (!cmd || !cmd->args[0])
    {
        // ft_free_args();
        return ;
    }
    char *wcd;
    (void)cmd;
    wcd = getcwd(NULL, 0);
    if (!wcd)
    {
        perror("getcwd is filed!");
        return ;
    }
    ft_putendl_fd(wcd, 1);

}
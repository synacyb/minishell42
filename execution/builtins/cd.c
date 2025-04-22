#include "../../minishell.h"

void    ft_cd(t_node   *cmd)
{
    if (cmd->args[1] == NULL)
    {
        char *home = getenv("HOME");
        if (!home)
        {
            perror("cd: HOME not set");
            return;
        }
        if (chdir(home) == -1)
            perror("cd");
    }
    else
    {
        if(chdir(cmd->args[1]) == -1)
            perror("cd");
    }
}

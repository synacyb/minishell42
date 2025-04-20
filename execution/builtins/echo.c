#include "../../minishell.h"

int check_fond_envs(char *arg)
{
    if(!arg || !(*arg))
        return (EXIT_FAILURE);
    if (arg[0] == '$')
        return (EXIT_SUCCESS);
    else
        return (EXIT_FAILURE);
    
}
char    *env_do(char *arg)
{
    return(getenv(arg + 1));
}
void    ft_echo(t_node   *cmd)
{
    char *env_var;
    int i = 1;
    int new_line = 1;
    if (!cmd || !cmd->args[0])
    {
        // ft_free_args();
        return ;
    }
    if(ft_strcmp(cmd->args[i], "-n") == 0)
    {
        new_line = 0;
        i++;
    }
        
    while (cmd->args[i])
    {
        if(check_fond_envs(cmd->args[i]) == EXIT_SUCCESS)
        {
            env_var = env_do(cmd->args[i]);
            ft_putstr_fd(env_var, 1);
        }
        else
            ft_putstr_fd(cmd->args[i], 1);
        if (cmd->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if(new_line == 1)
        printf("\n");
}

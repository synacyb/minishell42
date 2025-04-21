#include "../../minishell.h"

void    cheak_new_line(char *arg, int *new_line)
{
    int i = 0;
    if(!arg)
        return ;
    while (arg[i])
    {
        if(arg[i] == '-')
            i++;
        if(arg[i] == 'n')
            *new_line = 0;
        else
        {
            *new_line = 1;
            break;
        }
        i++;
    }
}
void    ft_echo(t_node   *cmd)
{
    int i = 1;
    int new_line = 1;
    if (!cmd || !cmd->args[0])
    {
        // ft_free_args();
        return ;
    }
    cheak_new_line(cmd->args[1], &new_line);
    if(new_line == 0)
        i++;
    while (cmd->args[i])
    {
        ft_putstr_fd(cmd->args[i], 1);
        if (cmd->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if(new_line == 1)
        printf("\n");
}

#include "../../minishell.h"

int    check_builtins_cmd(t_node *args, t_list *env)
{
    int check = 0;
    if (ft_strcmp(args->cmd, "echo") == 0)
        (ft_echo(args), check = 1);
    if(ft_strcmp(args->cmd, "pwd") == 0)
        (ft_pwd(args), check = 1);
    if(ft_strcmp(args->cmd, "env") == 0)
        (ft_env(env), check = 1);
    if(ft_strcmp(args->cmd, "cd") == 0)
        (ft_cd(args), check = 1);
    if(ft_strcmp(args->cmd, "export") == 0)
        (ft_export(args, env), check = 1);
    return check;
}
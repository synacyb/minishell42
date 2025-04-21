#include "../minishell.h"

void    exeuction_cmds(t_node *args, char **env)
{
    if(args->args[0] == NULL) // if the user send a empty string !
        return ;
    check_cmd(args, env);
}

int main(int ac, char **av, char **envp) 
{
    char *input;
    t_node *cmds = NULL;
    char **env;
    
    set_data(cmds);
    ((void)ac , (void)av);
    env = get_env(envp);
    while (1)
    {
        input = readline(COLOR_GREEN "minishell> " COLOR_RESET);
        if (!input)
            break;
        cmds = parse_input(input);
        exeuction_cmds(cmds, env);
    }
    return 0;
}


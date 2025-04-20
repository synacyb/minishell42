#include "minishell.h"

void    exeuction_cmds(t_cmd *args)
{
    check_cmd(args);
}

int main()
{
    char    *input;
    t_cmd cmd;
    while(1)
    {
        input = readline(COLOR_GREEN "minishell> " COLOR_RESET);
        t_command cmd_cpy = parse_input(input);
        cmd.cmd = cmd_cpy.cmd;
        for (int i = 0; i < MAX_ARGS && cmd_cpy.args[i]; i++) {
            cmd.args[i] = ft_strdup(cmd_cpy.args[i]);
        }
        exeuction_cmds(&cmd);
        // printf("Command: %s\n", cmd.cmd);
        // for (int i = 0; cmd.args[i]; i++)
        //     printf("Arg[%d]: %s\n", i, cmd.args[i]);

        // // Free allocated memory
        // for (int i = 0; cmd.args[i]; i++)
        //     free(cmd.args[i]);
        // free(cmd.cmd);
    }
}
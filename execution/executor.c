#include "../minishell.h"

void    exeuction_cmds(t_node *args)
{
    check_cmd(args);
}

int main(void) 
{
    char *input;
    t_node *cmds;

    while (1)
    {
        input = readline(COLOR_GREEN "minishell> " COLOR_RESET);
        if (!input)
            break;
        cmds = parse_input(input);
        exeuction_cmds(cmds);
    }
    return 0;
}

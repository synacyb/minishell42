#include "minishell.h"

void    exeuction_cmds(char **args)
{
    
}

int main()
{
    char    *input;
    char    **args;
    while(1)
    {
        input = readline(COLOR_GREEN "minishell> " COLOR_RESET);
        mini_parser(input);
        // exeuction_cmds(args);
        int i = 0;
        while (args[i] != NULL)
        {
            printf("%s\n", args[i]);
            i++;
        }
    }
}
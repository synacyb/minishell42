#include "../../minishell.h"

void    ft_env(char **env)
{
    int i = 0;

    while(env[i] != NULL)
    {
        printf("%s", env[i]);
        printf("\n");
        i++;
    }
}
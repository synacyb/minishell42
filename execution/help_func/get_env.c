#include "../../minishell.h"
int count_line(char **env)
{
    int i = 0;

    while(env[i] != NULL)
        i++;
    return i;
}
char    **get_env(char **enva)
{
    char **env;
    int i = 0;
    int len = count_line(enva);

    env = malloc((len + 1) * sizeof(char *));

    while (enva[i])
    {
        env[i] = ft_strdup(enva[i]);
        i++;
    }
    env[i] = NULL;
    return (env);
}
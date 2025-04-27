#include "../../minishell.h"

char **get_copy_of_env(t_list *env)
{
    int len = ft_lstsize(env);
    char **arr = malloc(sizeof(char *) * (len + 1));
    if (!arr)
        return NULL;

    int i = 0;
    while (env)
    {
        arr[i++] = ft_strdup((char *)env->content);
        env = env->next;
    }
    arr[i] = NULL;
    return arr;
}
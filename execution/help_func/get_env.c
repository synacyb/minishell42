#include "../../minishell.h"

t_list  *creat_list_env(char **env)
{
    int i;
    i = 0;

    t_list *env_list =  NULL;
    t_list *next_nod = NULL;
    while (env[i])
    {
        if(!env_list)
            env_list = ft_lstnew(env[i]);
        else
        {
            next_nod = ft_lstnew(env[i]);
            ft_lstadd_back(&env_list, next_nod);
        }
        i++;
    }
    return env_list;
}
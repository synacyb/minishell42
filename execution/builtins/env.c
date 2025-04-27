#include "../../minishell.h"

void    ft_env(t_list *env)
{
    char *equal;
    while (env != NULL)
    {
        equal = ft_strchr((char *)env->content, '=');
        if(equal)
        {
            printf("%s", (char *)env->content);
            printf("\n");
        }
        env = env->next;
    }
}
#include "../../minishell.h"

void    ft_env(t_list *env)
{
    while (env != NULL)
    {
        printf("%s", (char *)env->content);
        printf("\n");
        env = env->next;
    }
}
#include "../../../minishell.h"

char *get_path_variable(t_list *env)
{
    t_list *cpy;
    cpy = env;
    while (cpy)
    {
        if (ft_strncmp((char *)cpy->content, "PATH=", 5) == 0)
            return (ft_strdup((char *)cpy->content + 5));
        cpy = cpy->next;
    }
    return NULL;
}
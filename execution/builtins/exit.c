#include "../../minishell.h"

void    free_content(void   *content)
{
    free(content);
}

void free_node(t_node *node)
{
    if (!node)
        return;

    if (node->cmd)
        free(node->cmd);

    if (node->args)
    {
        int i = 0;
        while (node->args[i])
            free(node->args[i++]);
        free(node->args);
    }
    free(node);
}
void    exit_func(t_node *node, t_list **env)
{
    free_node(node);
    ft_lstclear(env, free_content);
    exit(0);
}
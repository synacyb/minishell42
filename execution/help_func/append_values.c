#include "../../minishell.h"

void    append_values(t_list *env, char *arg)
{
    char *key = get_clean_key(arg);
    char *value = ft_strdup(ft_strchr(arg, '=') + 1);
    char	*key_list;
	char	*value_list;
    char *joined;
    t_list *cpy_node;
    t_list *cpy_list = env;
    while (cpy_list)
    {
        get_value_and_key(&key_list, &value_list, cpy_list->content);
        if (ft_strcmp(key, key_list) == 0)
        {
            joined = ft_strjoin(cpy_list->content, value);
            free(cpy_list->content);
            cpy_list->content = joined;
            free(key);
            free(key_list);
            free(value);
            free(value_list);
            return ;
        }
        free(key_list);
        free(value_list);
        cpy_list = cpy_list->next;
    }
    char *tmp = key;
    key = ft_strjoin(key, "=");
    free(tmp);
    joined = ft_strjoin(key, value);
    cpy_node = ft_lstnew((void *)joined);
    ft_lstadd_back(&env, cpy_node);
}

#include "../../minishell.h"

void    free_extra(char *key, char *value)
{
    free(key);
    free(value);
}

void    add_new_var(t_list *env, char *arg)
{
    exporta data;
    char *joined;

    data.key_arg = get_clean_key(arg);
    data.value_arg = ft_strdup(ft_strchr(arg, '='));
    joined = ft_strjoin(data.key_arg, data.value_arg);
    data.cpy_node = ft_lstnew((void *)joined);
    ft_lstadd_back(&env, data.cpy_node);
    free_extra(data.key_arg, data.value_arg);
}

void    append_values(t_list *env, char *arg)
{
    char *joined;
    exporta data;

    data.cpy = env;
    data.key_arg = get_clean_key(arg);
    data.value_arg = ft_strdup(ft_strchr(arg, '=') + 1);
    while (data.cpy)
    {
        get_value_and_key(&data.key_list, &data.value_list, data.cpy->content);
        if (ft_strcmp(data.key_arg, data.key_list) == 0)
        {
            joined = ft_strjoin(data.cpy->content, data.value_arg);
            free(data.cpy->content);
            data.cpy->content = joined;
            free_extra(data.key_arg, data.value_arg);
            free_extra(data.key_list, data.value_list);
            return ;
        }
        free_extra(data.key_list, data.value_list);
        data.cpy = data.cpy->next;
    }
    free_extra(data.key_arg, data.value_arg);
    add_new_var(env, arg);
}

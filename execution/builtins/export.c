#include "../../minishell.h"

void    get_value_and_key(char **key, char **value, char  *arg)
{
    char *equal = ft_strchr(arg, '=');
    if (!equal)
    {
        *key = ft_strdup(arg);
        *value = NULL;
        return;
    }
    int len1 = ft_strlen(arg);
    int len2 = ft_strlen(equal);
    int target_len = len1 - len2;

    *key = ft_substr(arg, 0, target_len);
    *value = ft_strdup(equal + 1);
}

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

void sort_array(char **arr)
{
    int swapped = 1;
    int i;
    while (swapped)
    {
        swapped = 0;
        i = 0;
        while (arr[i + 1])
        {
            if (strcmp(arr[i], arr[i + 1]) > 0)
            {
                char *tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swapped = 1;
            }
            i++;
        }
    }
}
void    free_cpy_list(char **arr)
{
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

void    print_env(t_list *env)
{
    char **cpy_list;
    char    *key;
    char    *value;

    cpy_list = get_copy_of_env(env);
    sort_array(cpy_list);
    int i = 0;

    while(cpy_list[i])
    {
        char *equal = ft_strchr(cpy_list[i], '=');
        if(equal)
        {
            get_value_and_key(&key, &value, cpy_list[i]);
            printf("declare -x %s=\"%s\"\n", key, value);
            free(key);
            free(value);
        }
        else
            printf("declare -x %s=''\n", cpy_list[i]);
        i++;
    }
    free_cpy_list(cpy_list);
}

void update_or_add_to_env(t_list *env, char *arg)
{
    t_list *cpy = env;
    char *key_arg;
    char *value_arg;
    char *key_list;
    char *value_list;

    get_value_and_key(&key_arg, &value_arg, arg);
    while (cpy != NULL)
    {
        get_value_and_key(&key_list, &value_list, cpy->content);
        if (ft_strcmp(key_arg, key_list) == 0)
        {
            free(cpy->content);
            cpy->content = (void *)ft_strdup(arg);
            free(key_list);
            free(value_list);
            free(key_arg);
            free(value_arg);
            return;
        }
        free(key_list);
        free(value_list);
        cpy = cpy->next;
    }
    t_list *cpy_node = ft_lstnew((void *)ft_strdup(arg));
    ft_lstadd_back(&env, cpy_node);
    free(key_arg);
    free(value_arg);
}
void    ft_export(t_node *arg, t_list *env)
{
    int i = 1;
    if(arg->args[i] == NULL)
    {
        print_env(env);
        return ;
    }
    else
    {
        while (arg->args[i])
        {
            update_or_add_to_env(env, arg->args[i]);
            i++;
        }
    }
}

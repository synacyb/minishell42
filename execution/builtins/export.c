#include "../../minishell.h"

void    get_value_and_key(char **key, char **value, char  *arg)
{
    char *equal = ft_strchr(arg, '=');
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
            printf("declare -x %s\n", cpy_list[i]);
        i++;
    }
}
void    ft_export(t_node *arg, t_list *env)
{
    // char    *key;
    // char    *value;
    int i = 1;
    if(arg->args[i] == NULL)
    {
        print_env(env);
        return ;
    }
    // else
    // {
    //     while (arg->args[i])
    //     {
    //         //function that update the key or add new key with her valu! 
    //     }
        
    // }
}
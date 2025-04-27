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
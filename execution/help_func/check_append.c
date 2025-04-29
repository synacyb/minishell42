#include "../../minishell.h"

int    check_append(char *arg)
{
    char *key;
    int i = 0;
    int len = 0;

    while (arg[i])
    {
        len++;
        if (arg[i] == '=')
            break;
        i++;
    }
    i = 0;
    key = ft_substr(arg, 0, len);
    while (key[i])
    {
        if(key[i] == '+' && key[i + 1] == '=')
            return 1;
        i++;
    }
    return 0;
}
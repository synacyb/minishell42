#include "../../minishell.h"

int check_key(char *key)
{
    int i = 0;

    if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
    {
        printf("export: `%s': not a valid identifier\n", key);
        return 0;
    }

    while (key[i])
    {
        if (key[i] == '=')
            break;
        if (key[i] == '+' && key[i + 1] == '=')
            break;
        if (!ft_isalnum(key[i]) && key[i] != '_')
        {
            printf("export: `%s': not a valid identifier\n", key);
            return 0;
        }
        i++;
    }
    return 1;
}

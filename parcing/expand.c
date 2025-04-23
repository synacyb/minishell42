#include "../minishell.h"
char *get_env_value(const char *var, char **env)
{
    size_t  len;
    int  i;

    len = ft_strlen(var);
    i = 0;
    while(env[i])
    {
        if(ft_strncmp(var, env[i] , len) == 0 && env[i][len] == '=')
            return(ft_strdup(env[i] + len + 1));
        i++;
    }
    return(ft_strdup(""));
}


char *expand_value(const char *str, char **env, int last_status)
{
    char *key ;
    char *val;
    char *result;
    int i;

    i = 0;
    result = ft_calloc(1, 1);
    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            if (str[i] == '?')
            {
                result = ft_strjoin_free(result, ft_itoa(last_status));
                i++;
            }
            else if (ft_isalpha(str[i]) || str[i] == '_')
            {
                int start = i;
                while (ft_isalnum(str[i]) || str[i] == '_') i++;
                key = ft_substr(str, start, i - start);
                val = get_env_value(key, env);
                result = ft_strjoin_free(result, val);
                free(key);
            }
            else
            {
                char tmp[2] = {'$', '\0'};
                result = ft_strjoin_free(result, tmp);
            }
        }
        else
        {
            char tmp[2] = {str[i++], '\0'};
            result = ft_strjoin_free(result, tmp);
        }
    }

    return result;
}

void expand_tokens(t_token *tokens, char **env, int last_status)
{
    while (tokens)
    {
        if (tokens->type == TOKEN_WORD)
        {
            char *expanded = expand_value(tokens->value, env, last_status);
            free(tokens->value);
            tokens->value = expanded;
        }
        tokens = tokens->next;
    }
}

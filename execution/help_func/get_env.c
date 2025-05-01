#include "../../minishell.h"

void    creat_spicial_env(t_list **env_list)
{
    char *pwd;
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        perror("getcwd is filed!");
        return ;
    }
    char *joined = ft_strjoin("PWD=", pwd);
    free(pwd);
    *env_list = ft_lstnew((void *)joined);
}

t_list  *creat_list_env(char **env)
{
    int i;
    i = 0;

    t_list *env_list =  NULL;
    t_list *next_nod = NULL;
    
    if(env[i] != NULL)
    {
        while (env[i])
        {
            if(!env_list)
                env_list = ft_lstnew(ft_strdup(env[i]));
            else
            {
                next_nod = ft_lstnew(ft_strdup(env[i]));
                ft_lstadd_back(&env_list, next_nod);
            }
            i++;
        }   
    }
    else
        creat_spicial_env(&env_list);
    return env_list;
}

#include "../../../minishell.h"

void    free_exit(char **arr)
{
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}
void    *fond_cmd(char *cmd, char *path)
{
    int i;
    char **arr;

    i = 0;
    arr = ft_split(path, ':');
    if (!path)
        return (NULL);

    char *tmp = NULL;
    char *new = NULL;
    while (arr[i])
    {
        tmp = ft_strjoin(arr[i], "/");
        new = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(new, X_OK) == 0)
            return(free_exit(arr), new);

        free(new);
        i++;
    }
    free_exit(arr);
    return NULL;
}

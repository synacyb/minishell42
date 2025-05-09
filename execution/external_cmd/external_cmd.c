#include "../../minishell.h"

void     external_cmd(t_node *cmd, t_list *env)
{
    char *path = get_path_variable(env);
    char *valid_path = NULL;
    char **env_arr;
    env_arr = get_copy_of_env(env);
    if (path == NULL)
    {
        printf("No such file or directory\n");
        return ;
    }

    valid_path = (char *)fond_cmd(cmd->cmd, path);
    
    if(!valid_path)
    {
        printf("%s: command not found\n", cmd->cmd);
        return ;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
    }
    else if(pid == 0)
    {
        execve(valid_path, cmd->args, env_arr);
        perror("execv failed");
        exit(127);
    }
    int status;
    waitpid(pid, &status, 0);
   
    free(path);
    free(valid_path);
    return ;
}

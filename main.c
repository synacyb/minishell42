#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int g_exit_status = 0; // Required for $?

// Print the command nodes created by parse_input
void print_nodes(t_node *node)
{
    while (node)
    {
        printf("🔹 CMD: %s\n", node->cmd ? node->cmd : "(null)");
        if (node->args)
        {
            printf("   ARGS:");
            for (int i = 0; node->args[i]; i++)
                printf(" %s", node->args[i]);
            printf("\n");
        }
        if (node->infile)
            printf("   IN: %s\n", node->infile);
        if (node->outfile)
            printf("   OUT: %s (%s)\n", node->outfile, node->append ? "append" : "truncate");
        if (node->pipe_in)
            printf("   ⬅️  Piped In %d\n ", node->pipe_in);
        if (node->pipe_out)
            printf("   ➡️  Piped Out %d\n" ,node->pipe_out);

        printf("-----------\n");
        node = node->next;
    }
}

// Free memory from t_node chain
void free_nodes(t_node *node)
{
    t_node *tmp;
    while (node)
    {
        tmp = node->next;
        if (node->cmd)
            free(node->cmd);
        if (node->infile)
            free(node->infile);
        if (node->outfile)
            free(node->outfile);
        if (node->args)
        {
            for (int i = 0; node->args[i]; i++)
                free(node->args[i]);
            free(node->args);
        }
        free(node);
        node = tmp;
    }
}

// int main(int ac, char **av, char **envp)
// {
//     char *input;
//     t_node *cmds = NULL;

//     (void)ac;
//     (void)av;

//     while (1)
//     {
//         input = readline("\033[0;32mminishell> \033[0m");
//         if (!input)
//             break;
//         if (*input)
//             add_history(input);

//         cmds = parse_input1(input, envp, g_exit_status);
//         if (cmds)
//         {
//             printf("\n🧠 Parsed Commands:\n");
//             print_nodes(cmds);
//             free_nodes(cmds);
//         }
//         else
//         {
//             printf("❌ Error: Invalid syntax or failed to tokenize\n");
//         }

//         free(input);
//     }

//     return 0;
// }
int count_pipes(t_node *node)
{
    int pipes = 0;
    while (node)
    {
        pipes++;
        node = node->next;
    }
    return (pipes);
}
void exeuction_speciale(t_node *nodes, t_list **env)
{
    int num_cmds = count_pipes(nodes);
    int pipes_needed = num_cmds - 1;
    int pipe_fds[2 * pipes_needed];
    int i = 0;
    t_node *current = nodes;

    // Create all pipes needed
    while (i < pipes_needed)
    {
        if (pipe(pipe_fds + i * 2) < 0)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    i = 0;
    current = nodes;
    while (current)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (i != 0)
            {
                dup2(pipe_fds[(i - 1) * 2], 0);
            }
            if (current->next)
            {
                dup2(pipe_fds[i * 2 + 1], 1);
            }
            for (int j = 0; j < 2 * pipes_needed; j++)
                close(pipe_fds[j]);
            exeuction_cmds(current, env);
            exit(EXIT_FAILURE);
        }

        current = current->next;
        i++;
    }

    // PARENT: close all pipe fds
    for (int j = 0; j < 2 * pipes_needed; j++)
        close(pipe_fds[j]);

    // Wait for all children
    for (int k = 0; k < num_cmds; k++)
        wait(NULL);
}

int main(int ac, char **av, char **envp)
{
    char *input;
    t_node *cmds = NULL;
    t_list *env = NULL;

    env = creat_list_env(envp);
    set_data(cmds);
    ((void)ac , (void)av);
    while (1)
    {
        input = readline(COLOR_GREEN "minishell> " COLOR_RESET);
        if (!input)
            break;
        add_history(input);
        if(input[0] != '\0')
        {
            cmds = parse_input1(input, envp, g_exit_status);
            if(cmds->next == NULL)
                exeuction_cmds(cmds, &env);
            else
            {
                exeuction_speciale(cmds, &env);
            }
        }
    }
    return 0;
}

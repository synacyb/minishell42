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
            printf("   ⬅️  Piped In\n");
        if (node->pipe_out)
            printf("   ➡️  Piped Out\n");

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

int main(int ac, char **av, char **envp)
{
    char *input;
    t_node *cmds = NULL;

    (void)ac;
    (void)av;

    while (1)
    {
        input = readline("\033[0;32mminishell> \033[0m");
        if (!input)
            break;
        if (*input)
            add_history(input);

        cmds = parse_input1(input, envp, g_exit_status);
        if (cmds)
        {
            printf("\n🧠 Parsed Commands:\n");
            print_nodes(cmds);
            free_nodes(cmds);
        }
        else
        {
            printf("❌ Error: Invalid syntax or failed to tokenize\n");
        }

        free(input);
    }

    return 0;
}

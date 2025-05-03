#include "../minishell.h"

// Count how many words (for malloc)
int count_words(char *line) {
    int count = 0;
    char *tmp = strtok(line, " ");
    while (tmp) {
        count++;
        tmp = strtok(NULL, " ");
    }
    return count;
}

t_node *parse_input(char *input)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node) return NULL;

    node->infile = NULL;
    node->outfile = NULL;
    node->append = 0;
    node->pipe_in = 0;
    node->pipe_out = 0;
    node->next = NULL;

    // duplicate because strtok modifies it
    char *dup = strdup(input);
    if (!dup) return NULL;

    int count = count_words(strdup(input)); // second strdup since count_words uses strtok
    node->args = malloc(sizeof(char *) * (count + 1));

    char *token = strtok(dup, " ");
    int i = 0;
    while (token) {
        node->args[i++] = ft_strdup(token);
        token = strtok(NULL, " ");
    }
    node->args[i] = NULL;
    node->cmd = ft_strdup(node->args[0]); // first token is the command

    free(dup);
    return node;
}
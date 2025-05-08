#include "minishell.h"

static t_node *new_node()
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return NULL;
    node->cmd = NULL;
    node->args = NULL;
    node->infile = NULL;
    node->outfile = NULL;
    node->append = 0;
    node->pipe_in = 0;
    node->pipe_out = 0;
    node->next = NULL;
    return node;
}

static char **list_to_array(t_list *lst)
{
    int count = ft_lstsize(lst);
    char **arr = malloc(sizeof(char *) * (count + 1));
    int i = 0;

    if (!arr)
        return NULL;
    while (lst)
    {
        arr[i++] = lst->content;
        lst = lst->next;
    }
    arr[i] = NULL;
    return arr;
}

static t_node *build_nodes(t_token *tokens)
{
    t_node *head = new_node();
    t_node *cur = head;
    t_list *args = NULL;

    while (tokens)
    {
        if (tokens->type == TOKEN_WORD)
        {
            ft_lstadd_back(&args, ft_lstnew(ft_strdup(tokens->value)));
        }
        else if (tokens->type == TOKEN_REDIR_IN)
        {
            tokens = tokens->next;
            if (tokens)
                cur->infile = ft_strdup(tokens->value);
        }
        else if (tokens->type == TOKEN_REDIR_OUT)
        {
            tokens = tokens->next;
            if (tokens)
            {
                cur->outfile = ft_strdup(tokens->value);
                cur->append = 0;
            }
        }
        else if (tokens->type == TOKEN_REDIR_APPEND)
        {
            tokens = tokens->next;
            if (tokens)
            {
                cur->outfile = ft_strdup(tokens->value);
                cur->append = 1;
            }
        }
        else if (tokens->type == TOKEN_PIPE)
        {
            cur->args = list_to_array(args);
            if (cur->args && cur->args[0])
                cur->cmd = ft_strdup(cur->args[0]);
            args = NULL;
            cur->pipe_out = 1;

            cur->next = new_node();
            cur->next->pipe_in = 1;
            cur = cur->next;
        }
        tokens = tokens->next;
    }

    if (cur)
    {
        cur->args = list_to_array(args);
        if (cur->args && cur->args[0])
            cur->cmd = ft_strdup(cur->args[0]);
    }

    return head;
}

t_node *parse_input1(const char *input, char **env, int last_status)
{
    t_token *tokens;
    t_node *commands = NULL;

    tokens = tokenizer(input);
    if (!tokens)
        return NULL;

    if (!check_syntax(tokens))
    {
        fprintf(stderr, "Syntax error\n");
        free_tokens(tokens);
        return NULL;
    }

    expand_tokens(tokens, env, last_status);
    commands = build_nodes(tokens);
    free_tokens(tokens);
    return commands;
}

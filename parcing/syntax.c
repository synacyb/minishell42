#include "minishell.h"

// Check if the token is a redirection operator
bool is_redirection(t_token_type type)
{
    return (
        type == TOKEN_REDIR_IN ||
        type == TOKEN_REDIR_OUT ||
        type == TOKEN_REDIR_APPEND ||
        type == TOKEN_HEREDOC
    );
}

// Check for syntax errors in the token list
bool check_syntax(t_token *tokens)
{
    t_token *cur;

    // Empty command is invalid
    if (!tokens)
        return false;

    // Start with pipe → error
    if (tokens->type == TOKEN_PIPE)
        return false;

    cur = tokens;
    while (cur)
    {
        // Double pipe or pipe at end
        if (cur->type == TOKEN_PIPE)
        {
            if (!cur->next || cur->next->type == TOKEN_PIPE)
                return false;
        }

        // Redirection followed by NULL or non-WORD token
        if (is_redirection(cur->type))
        {
            if (!cur->next || cur->next->type != TOKEN_WORD)
                return false;
        }

        cur = cur->next;
    }

    return true;
}


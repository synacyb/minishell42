
#include "../minishell.h"

//------------------------- UTILITY FUNCTIONS -----------------------------//

bool is_operator_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

void add_token(t_token **head, t_token_type type, const char *val , int len)
{
    t_token *new;
    t_token *cur;

    new = malloc(sizeof(t_token));
    if (!new)
        return; // handle malloc failure

    new->type = type;
    new->value = ft_substr(val, 0, len);
    new->next = NULL;

    if (!*head)
        *head = new;
    else
    {
        cur = *head;
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
}

//------------------------- TOKENIZER CORE -----------------------------//

t_token_type get_operator_type(const char *str, int *skip)
{
    if (strncmp(str, ">>", 2) == 0)
    {
        *skip = 2;
        return TOKEN_REDIR_APPEND;
    }
    if (strncmp(str, "<<", 2) == 0)
    {
        *skip = 2;
        return TOKEN_HEREDOC;
    }
    if (str[0] == '>')
    {
        *skip = 1;
        return TOKEN_REDIR_OUT;
    }
    if (str[0] == '<')
    {
        *skip = 1;
        return TOKEN_REDIR_IN;
    }
    if (str[0] == '|')
    {
        *skip = 1;
        return TOKEN_PIPE;
    }
    return TOKEN_WORD;
}

char *parse_quoted(const char *input, int *i, char quote)
{
    int start;
    char *quoted;

    start = ++(*i);
    while (input[*i] && input[*i] != quote)
        (*i)++;
    quoted = ft_substr(input, start, *i - start);
    if (input[*i] == quote)
        (*i)++;
    return quoted;
}

t_token *tokenizer(const char *input)
{
    t_token *tokens = NULL;
    t_token_type type;
    char quote;
    char *quoted;
    int i ;
    int skip;
    int start;

    i = 0;
    while (input[i])
    {
        while ((input[i] >= 9 && input[i] <= 13) || input[i] == ' ')
            i++;
        if (!input[i])
            break;

        if (input[i] == '"' || input[i] == '\'')
        {
            quote = input[i];
            quoted = parse_quoted(input, &i, quote);
            add_token(&tokens, TOKEN_WORD, quoted, ft_strlen(quoted));
            free(quoted);
        }
        else if (is_operator_char(input[i]))
        {
            skip = 0;
            type = get_operator_type(&input[i], &skip);
            add_token(&tokens, type, &input[i], skip);
            i += skip;
        }
        else
        {
            start = i;
            while (input[i] && !is_operator_char(input[i]) &&
                   input[i] != ' ' && (input[i] < 9 || input[i] > 13) &&
                   input[i] != '\'' && input[i] != '"')
            {
                i++;
            }
            add_token(&tokens, TOKEN_WORD, &input[start], i - start);
        }
    }
    return tokens;
}

//------------------------- DEBUG TESTING -----------------------------//

void print_tokens(t_token *t)
{
    while (t)
    {
        printf("[%d] '%s'\\n", t->type, t->value);
        printf("\n");
        t = t->next;
    }
}

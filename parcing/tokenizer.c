
// minishell_tokenizer.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//------------------------- TOKEN DEFINITIONS -----------------------------//

typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC
} t_token_type;

typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

//------------------------- UTILITY FUNCTIONS -----------------------------//

bool is_operator_char(char c) {
    return c == '|' || c == '<' || c == '>';
}

char *substr(const char *src, int start, int len) {
    char *out = malloc(len + 1);
    strncpy(out, src + start, len);
    out[len] = '\0';
    return out;
}

void add_token(t_token **head, t_token_type type, const char *val, int len) {
    t_token *new = malloc(sizeof(t_token));
    new->type = type;
    new->value = substr(val, 0, len);
    new->next = NULL;

    if (!*head) *head = new;
    else {
        t_token *cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = new;
    }
}

//------------------------- TOKENIZER CORE -----------------------------//

t_token_type get_operator_type(const char *str, int *skip) {
    if (strncmp(str, ">>", 2) == 0) { *skip = 2; return TOKEN_REDIR_APPEND; }
    if (strncmp(str, "<<", 2) == 0) { *skip = 2; return TOKEN_HEREDOC; }
    if (str[0] == '>') { *skip = 1; return TOKEN_REDIR_OUT; }
    if (str[0] == '<') { *skip = 1; return TOKEN_REDIR_IN; }
    if (str[0] == '|') { *skip = 1; return TOKEN_PIPE; }
    return TOKEN_WORD;
}

char *parse_quoted(const char *input, int *i, char quote) {
    int start = ++(*i);
    while (input[*i] && input[*i] != quote) (*i)++;
    char *quoted = substr(input, start, *i - start);
    (*i)++; // skip closing quote
    return quoted;
}

t_token *tokenize(const char *input) {
    t_token *tokens = NULL;
    int i = 0;
    while (input[i]) {
        while (isspace(input[i])) i++;
        if (!input[i]) break;

        if (input[i] == '"' || input[i] == '\'') {
            char quote = input[i];
            char *quoted = parse_quoted(input, &i, quote);
            add_token(&tokens, TOKEN_WORD, quoted, strlen(quoted));
            free(quoted);
        }
        else if (is_operator_char(input[i])) {
            int skip = 0;
            t_token_type type = get_operator_type(&input[i], &skip);
            add_token(&tokens, type, &input[i], skip);
            i += skip;
        } else {
            int start = i;
            while (input[i] && !isspace(input[i]) && !is_operator_char(input[i])) {
                if (input[i] == '"' || input[i] == '\'') break;
                i++;
            }
            add_token(&tokens, TOKEN_WORD, &input[start], i - start);
        }
    }
    return tokens;
}

//------------------------- DEBUG TESTING -----------------------------//

void print_tokens(t_token *t) {
    while (t) {
        printf("[%d] '%s'\n", t->type, t->value);
        t = t->next;
    }
}

int main(void) {
    const char *test = "echo \"Hello world\" > file.txt | grep hello";
    t_token *tokens = tokenize(test);
    print_tokens(tokens);
    return 0;
}



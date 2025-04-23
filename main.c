
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int g_exit_status = 0;

int main(int ac, char **av, char **envp)
{
    char *input;
    t_token *tokens;
    char **env = envp; // can duplicate if needed

    (void)ac;
    (void)av;

    while (1)
    {
        input = readline(COLOR_GREEN "minishell> " COLOR_RESET);
        if (!input)
            break;

        if (*input)
            add_history(input);

        tokens = tokenizer(input);

        if (!tokens)
        {
            free(input);
            continue;
        }

        if (!check_syntax(tokens))
        {
            printf("Syntax error!\n");
            free_tokens(tokens);
            free(input);
            continue;
        }

        // Expand environment vars and $?
        expand_tokens(tokens, env, g_exit_status);

        // Debug: print final tokens
        printf("🔍 Final tokens:\n");
        print_tokens(tokens);

        // Simulate success (or set manually if you test $?)
        g_exit_status = 0;

        free_tokens(tokens);
        free(input);
    }

    return 0;
}
=======
// hada dyalk nta !!! bach mli ghatkamal parcing tsift liya linkdlest l execution.c !
>>>>>>> 417bbe61606d6354cf0536fafac2513a0ca9d115


#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

// int g_exit_status = 0;

// int main(int ac, char **av, char **envp)
// {
//     char *input;
//     t_token *tokens;
//     char **env = envp; // can duplicate if needed

//     (void)ac;
//     (void)av;

//     while (1)
//     {
//         input = readline(COLOR_GREEN "minishell> " COLOR_RESET);
//         if (!input)
//             break;

//         if (*input)
//             add_history(input);

//         tokens = tokenizer(input);

//         if (!tokens)
//         {
//             free(input);
//             continue;
//         }

//         if (!check_syntax(tokens))
//         {
//             printf("Syntax error!\n");
//             free_tokens(tokens);
//             free(input);
//             continue;
//         }

//         // Expand environment vars and $?
//         expand_tokens(tokens, env, g_exit_status);

//         // Debug: print final tokens
//         printf("🔍 Final tokens:\n");
//         print_tokens(tokens);

//         // Simulate success (or set manually if you test $?)
//         g_exit_status = 0;

//         free_tokens(tokens);
//         free(input);
//     }

//     return 0;
// }

//had dyali  commintyh okml khdmtak !!!
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
        cmds = parse_input(input);
        exeuction_cmds(cmds, env);
    }
    
    return 0;
}

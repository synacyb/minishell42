#ifndef MINISHELL_H
 #define MINISHELL_H
 #include <unistd.h>
 #include <stdlib.h>
 #include "libft_v1/libft.h"
 #include <readline/readline.h>
 #include <readline/history.h>
 #include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

 
 // ----- Colors -----
 #define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN "\001\033[0;32m\002"
#define COLOR_RESET "\001\033[0m\002"
 #define COLOR_YELLOW  "\033[0;33m"
 #define COLOR_BLUE    "\033[0;34m"
 #define COLOR_MAGENTA "\033[0;35m"
 #define COLOR_CYAN    "\033[0;36m"
 #define COLOR_WHITE   "\033[0;37m"
 #define COLOR_BOLD    "\033[1m"
 
 // ----- struct that apande all info about cmd ------
 typedef struct s_node
 {
    char *cmd;
    char **args;
    char *infile;
    char *outfile;
    int append;
    int pipe_in;
    int pipe_out;
    struct s_node *next;
} t_node;

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

typedef struct export_data
{
    t_list	*cpy;
	char	*key_arg;
	char	*value_arg;
	char	*key_list;
	char	*value_list;
	t_list	*cpy_node;
    char    **cpy_list;
    char    *equal;
}exporta;

struct e_minishell
{
    t_node *node;
    t_token *type;
};

t_node *parse_input(char *input);
void    set_data(t_node *data);
void    check_cmd(t_node *args, t_list **env);
void    ft_echo(t_node   *cmd);
void    ft_pwd(t_node   *cmd);
void    remove_variable(t_list **env, t_node *arg);
void    ft_export(t_node *arg, t_list *env);
int    check_builtins_cmd(t_node *args, t_list **env);
void    get_value_and_key(char **key, char **value, char  *arg);
char **get_copy_of_env(t_list *env);
char *get_path_variable(t_list *env);
void     external_cmd(t_node *cmd, t_list *env);
void    *fond_cmd(char *cmd, char *path);
void sort_array(char **arr);
t_list  *creat_list_env(char **env);
void    ft_env(t_list *env);
void    ft_cd(t_node   *cmd);
int check_key(char *key);
void exit_func(t_node *node, t_list **env);
void	print_env(t_list *env);
char *get_clean_key(char *arg);
void    exeuction_cmds(t_node *args, t_list **env);
t_token *tokenizer(const char *input);
void print_tokens(t_token *t);
bool check_syntax(t_token *tokens);
void    expand_tokens(t_token *tokens, char **env, int last_status);
void free_tokens(t_token *tokens);
t_node *parse_input1(const char *input, char **env, int last_status);

#endif
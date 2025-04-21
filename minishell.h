#ifndef MINISHELL_H
 #define MINISHELL_H
 #include <unistd.h>
 #include <stdlib.h>
 #include "libft_v1/libft.h"
 #include <readline/readline.h>
 #include <readline/history.h>
 
 // ----- Colors -----
 #define COLOR_RESET   "\033[0m"
 #define COLOR_RED     "\033[0;31m"
 #define COLOR_GREEN   "\033[0;32m"
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

t_node *parse_input(char *input);
void    set_data(t_node *data);
void    check_cmd(t_node *args, char **env);
void    ft_echo(t_node   *cmd);
void    ft_pwd(t_node   *cmd);
int    check_builtins_cmd(t_node *args, char **env);
char    **get_env(char **enva);
void    ft_env(char **env);

#endif
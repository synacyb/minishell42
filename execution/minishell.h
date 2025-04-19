#ifndef MINISHELL_H
#define MINISHELL_H
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
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
typedef struct s_cmd {
    char **argv;       // ["grep", "word"]
    char *infile;      // input redirection
    char *outfile;     // output redirection
    int append;        // 1 if >>, 0 if >
    int pipe_in;       // 1 if input from previous pipe
    int pipe_out;      // 1 if output to next pipe
} t_cmd;

char **mini_parser(const char *input);
void    check_builtins_cmd(char **cmd);
#endif
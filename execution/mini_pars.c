#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 10

typedef struct s_command {
    char *cmd;
    char *args[MAX_ARGS];
} t_command;

t_command parse_input(const char *input) {
    t_command command = {0};
    char *token;
    char *input_copy = strdup(input);
    int i = 0;

    token = strtok(input_copy, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        if (i == 0)
            command.cmd = strdup(token);
        command.args[i++] = strdup(token);
        token = strtok(NULL, " ");
    }
    command.args[i] = NULL;
    free(input_copy);
    return command;
}

// int main() {
//     const char *input = "ls -la /home";
//     t_command cmd = parse_input(input);

//     printf("Command: %s\n", cmd.cmd);
//     for (int i = 0; cmd.args[i]; i++)
//         printf("Arg[%d]: %s\n", i, cmd.args[i]);

//     // Free allocated memory
//     for (int i = 0; cmd.args[i]; i++)
//         free(cmd.args[i]);
//     free(cmd.cmd);

//     return 0;
// }
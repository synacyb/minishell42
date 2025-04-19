#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ARGS 128

char *substr(const char *src, int start, int end) {
    int len = end - start;
    char *str = malloc(len + 1);
    if (!str) return NULL;
    for (int i = 0; i < len; i++)
        str[i] = src[start + i];
    str[len] = '\0';
    return str;
}

bool is_special_char(char c) {
    return c == '|' || c == '<' || c == '>';
}

char **mini_parser(const char *input) {
    char **arr = malloc(sizeof(char *) * MAX_ARGS);
    int i = 0, start = 0, idx = 0;
    bool in_quote = false;

    while (input[i]) {
        if (input[i] == '"') {
            in_quote = !in_quote;
            i++;
        } else if ((input[i] == ' ' || input[i] == '\t') && !in_quote) {
            if (i > start)
                arr[idx++] = substr(input, start, i);
            while (input[i] == ' ' || input[i] == '\t') i++;
            start = i;
        } else if (is_special_char(input[i]) && !in_quote) {
            if (i > start)
                arr[idx++] = substr(input, start, i);
            arr[idx++] = substr(input, i, i + 1);
            i++;
            start = i;
        } else {
            i++;
        }
    }

    if (i > start)
        arr[idx++] = substr(input, start, i);
    arr[idx] = NULL;
    return arr;
}

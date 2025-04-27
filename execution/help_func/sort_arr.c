#include "../../minishell.h"

void sort_array(char **arr)
{
    int swapped = 1;
    int i;
    while (swapped)
    {
        swapped = 0;
        i = 0;
        while (arr[i + 1])
        {
            if (strcmp(arr[i], arr[i + 1]) > 0)
            {
                char *tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swapped = 1;
            }
            i++;
        }
    }
}
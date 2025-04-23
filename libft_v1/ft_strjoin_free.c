#include <stdlib.h>
#include "libft.h" 

char *ft_strjoin_free(char *s1, const char *s2)
{
    char *joined;

    if (!s1 && !s2)
        return NULL;
    else if (!s1)
        return ft_strdup(s2);
    else if (!s2)
        return s1;

    joined = ft_strjoin(s1, s2);
    free(s1);
    return joined;
}


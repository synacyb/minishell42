#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	while (str1 && (*str1 != '\0' || *str2 != '\0'))
	{
		if (*str1 != *str2)
			return ((unsigned char)*str1 - (unsigned char)*str2);
		str1++;
		str2++;
	}
	return (0);
}
#include "../../minishell.h"

char *get_clean_key(char *arg)
{
	int i = 0;

	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			break;
		if (arg[i] == '=')
			break;
		i++;
	}

	return ft_substr(arg, 0, i);
}
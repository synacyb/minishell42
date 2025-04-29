#include "../../minishell.h"

void	free_cpy_list(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_extra_alocation(char *key, char *value)
{
	free(key);
	free(value);
}
void	print_env(t_list *env)
{
	char	**cpy_list;
	char	*key;
	char	*value;
	int		i;
	char	*equal;

	cpy_list = get_copy_of_env(env);
	sort_array(cpy_list);
	i = 0;
	while (cpy_list[i])
	{
		equal = ft_strchr(cpy_list[i], '=');
		if (equal)
		{
			get_value_and_key(&key, &value, cpy_list[i]);
			printf("declare -x %s=\"%s\"\n", key, value);
			free(key);
			free(value);
		}
		else
			printf("declare -x %s\n", cpy_list[i]);
		i++;
	}
	free_cpy_list(cpy_list);
}

void	update_or_add_to_env(t_list *env, char *arg, int append)
{
	exporta data;
	data.cpy = env;
	if(append == 1)
	{
		append_values(env, arg);
		return ;
	}
	get_value_and_key(&data.key_arg, &data.value_arg, arg);
	while (data.cpy != NULL)
	{
		get_value_and_key(&data.key_list, &data.value_list, data.cpy->content);
		if (ft_strcmp(data.key_arg, data.key_list) == 0)
		{
			free(data.cpy->content);
			data.cpy->content = (void *)ft_strdup(arg);
			free_extra_alocation(data.key_list, data.value_list);
			free_extra_alocation(data.key_arg, data.value_arg);
			return ;
		}
		free_extra_alocation(data.key_list, data.value_list);
		data.cpy = data.cpy->next;
	}
	data.cpy_node = ft_lstnew((void *)ft_strdup(arg));
	ft_lstadd_back(&env, data.cpy_node);
	free_extra_alocation(data.key_arg, data.value_arg);
}
void	ft_export(t_node *arg, t_list *env)
{
	int	i;
	int append;
	i = 1;
	if (arg->args[i] == NULL)
	{
		print_env(env);
		return ;
	}
	else
	{
		while (arg->args[i])
		{
			append = 0;
			if(check_append(arg->args[i]) == 1)
				append = 1;
			if(check_key(arg->args[i]))
				update_or_add_to_env(env, arg->args[i], append);
			i++;
		}
	}
}

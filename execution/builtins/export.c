/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:42:53 by ayadouay          #+#    #+#             */
/*   Updated: 2025/04/30 09:09:38 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	new_var(t_list *env, char *arg)
{
	exporta	data;

	data.cpy_node = ft_lstnew((void *)ft_strdup(arg));
	ft_lstadd_back(&env, data.cpy_node);
}
void	check_extra_case(exporta *data, char *arg)
{
	int i = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
            break;
        i++;
    }
	if(arg[i] == '=')
	{
		free(data->cpy->content);
		data->cpy->content = (void *)ft_strdup(arg);
		free_extra_alocation(data->key_list, data->value_list);
		free_extra_alocation(data->key_arg, data->value_arg);
	}
}
void	update_or_add_to_env(t_list *env, char *arg, int append)
{
	exporta	data;

	data.cpy = env;
	if (append == 1)
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
			check_extra_case(&data, arg);
			return ;
		}
		free_extra_alocation(data.key_list, data.value_list);
		data.cpy = data.cpy->next;
	}
	new_var(env, arg);
	free_extra_alocation(data.key_arg, data.value_arg);
}

void	ft_export(t_node *arg, t_list *env)
{
	int	i;
	int	append;

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
			if (check_append(arg->args[i]) == 1)
				append = 1;
			if (check_key(arg->args[i]))
				update_or_add_to_env(env, arg->args[i], append);
			i++;
		}
	}
}

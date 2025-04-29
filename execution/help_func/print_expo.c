/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:43:24 by ayadouay          #+#    #+#             */
/*   Updated: 2025/04/29 15:44:10 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_extra_memory(char *key, char *value)
{
	free(key);
	free(value);
}

void	free_list(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	print_env(t_list *env)
{
	int		i;
	exporta	data;

	data.cpy_list = get_copy_of_env(env);
	i = 0;
	sort_array(data.cpy_list);
	while (data.cpy_list[i])
	{
		data.equal = ft_strchr(data.cpy_list[i], '=');
		if (data.equal)
		{
			get_value_and_key(&data.key_arg, &data.value_arg, data.cpy_list[i]);
			printf("declare -x %s=\"%s\"\n", data.key_arg, data.value_arg);
			free_extra_memory(data.key_arg, data.value_arg);
		}
		else
			printf("declare -x %s\n", data.cpy_list[i]);
		i++;
	}
	free_list(data.cpy_list);
}

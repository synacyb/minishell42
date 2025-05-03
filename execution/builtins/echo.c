/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:22:24 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/02 09:18:12 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cheak_new_line(char **arg, int *new_line, int *i)
{
	int	j;

	while (arg[*i])
	{
		j = 0;
		if (arg[(*i)][j] == '-')
			j++;
		else
			break ;
		while (arg[(*i)][j])
		{
			if (arg[(*i)][j] == 'n')
				*new_line = 0;
			else
			{
				*new_line = 1;
				break ;
			}
			j++;
		}
		if (*new_line == 1)
			break ;
		(*i)++;
	}
}

void	ft_echo(t_node	*cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	cheak_new_line(cmd->args, &new_line, &i);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line == 1)
		printf("\n");
}

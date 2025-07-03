/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:35:40 by alraltse          #+#    #+#             */
/*   Updated: 2025/07/03 12:37:15 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_echo_args(char **result, int k)
{
	int	args_count;

	args_count = 0;
	while (result[k])
	{
		if (ft_strcmp(result[k], "|") == 0)
			break ;
		args_count++;
		k++;
	}
	return (args_count);
}

int	count_normal_args(char **result, t_node *current_node, int k)
{
	int	args_count;
	int	res;

	args_count = 0;
	res = 0;
	if (k <= 0)
		return (0);
	while (result[k])
	{
		if (ft_strcmp(result[k], "|") == 0)
			break ;
		res = condition_is_met(current_node, result, k);
		if (res == 0)
			args_count++;
		k++;
	}
	return (args_count);
}

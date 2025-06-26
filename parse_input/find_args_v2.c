/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:30:00 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/15 16:58:39 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args2(char **result, t_node *current_node, int k)
{
	int		args_count;

	args_count = 0;
	current_node->args_count = 0;
	while (result[k])
	{
		if (ft_strcmp(result[k], "|") == 0)
			break ;
		if (condition_is_met(current_node, result, k) == 0)
			args_count++;
		k++;
	}
	return (args_count);
}

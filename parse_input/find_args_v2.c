/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:30:00 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/21 16:15:39 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args2(char **result, t_node *current_node, int k)
{
	int		args_count;
	int		i;

	i = k;
	args_count = 0;
	current_node->args_count = 0;
	while (result[i])
	{
		if (ft_strcmp(result[i], "|") == 0)
			break ;
		if (condition_is_met(current_node, result, i) == 0)
			args_count++;
		i++;
	}
	return (args_count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/06/23 20:29:37 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_flags(char **result, int j)
{
	int	flags_count;
	int n_flag_found;

	n_flag_found = 0;
	flags_count = 0;
	while (result[j])
	{
		if (ft_strcmp(result[j], "|") == 0)
			break ;
		if (ft_strcmp(result[0], "echo") == 0 && ft_strcmp(result[1], "-n") == 0 && !n_flag_found)
		{
			flags_count++;
			n_flag_found = 1;
		}
		else if (ft_strcmp(result[0], "echo") != 0 && ft_strcmp(result[1], "-n") != 0 && !n_flag_found && result[j][0] == '-' && result[j][1] != '$')
			flags_count++;
		j++;
	}
	return (flags_count);
}


void	find_flags(char *result, t_node *current_node, int *i)
{
	int n_flag_found;

	n_flag_found = 0;
	
	if (ft_strcmp(current_node->cmd, "echo") == 0 && ft_strcmp(result, "-n") == 0 && !n_flag_found)
	{
		if (result[3] && result[4] && result[3] == '-' && result[4] == 'n')
			result += 2;
		current_node->flags[*i] = ft_strdup2(result);
		current_node->fcmd = ft_strjoin_free(current_node->fcmd, result);
		n_flag_found = 1;
		(*i)++;
		return ;
	}
	if (result[0] == '-' && result[1] != '$')
	{
		current_node->flags[*i] = ft_strdup2(result);
		current_node->fcmd = ft_strjoin_free(current_node->fcmd, result);
		(*i)++;
	}
}

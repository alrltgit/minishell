/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/07/02 16:17:07 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_flag_for_echo(char **result, int *n_flag_found)
{
	if (ft_strcmp(result[0], "echo") == 0
		&& ft_strcmp(result[1], "-n") == 0 && !(*n_flag_found))
	{
		*n_flag_found = 1;
		return (1);
	}
	return (0);
}

int	is_flag_for_other(char **result, int j, int *n_flag_found)
{
	if (ft_strcmp(result[0], "echo") != 0
		&& ft_strcmp(result[1], "-n") == 0
		&& !(*n_flag_found) && result[j][0] == '-' && result[j][1] != '$')
		return (1);
	if (ft_strcmp(result[0], "echo") != 0
		&& ft_strcmp(result[1], "-n") != 0
		&& !(*n_flag_found) && result[j][0] == '-' && result[j][1] != '$')
		return (1);
	return (0);
}

int	count_flags(char **result, int j)
{
	int	flags_count;
	int	n_flag_found;

	flags_count = 0;
	n_flag_found = 0;
	while (result[j])
	{
		if (ft_strcmp(result[j], "|") == 0)
			break ;
		if (is_flag_for_echo(result, &n_flag_found))
			flags_count++;
		else if (is_flag_for_other(result, j, &n_flag_found))
			flags_count++;
		j++;
	}
	return (flags_count);
}

void	find_flags(char *res, t_node *current_node, int *i)
{
	if (ft_strcmp(current_node->cmd, "echo") == 0
		&& ft_strcmp(res, "-n") == 0 && current_node->n_flag == 0)
	{
		current_node->flags[0] = ft_strdup(res);
		current_node->fcmd = ft_strjoin_free(current_node->fcmd, res);
		current_node->n_flag = 1;
		(*i)++;
		return ;
	}
	if (res[0] == '-' && res[1] != '$'
		&& current_node->n_flag == 0)
		// && (res[2] == ' ' || res[2] == '\0'))
	{
		current_node->flags[*i] = ft_strdup(res);
		current_node->fcmd = ft_strjoin_free(current_node->fcmd, res);
		(*i)++;
		return ;
	}
}

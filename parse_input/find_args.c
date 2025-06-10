/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:43:30 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/09 21:27:52 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	allocate_args_memory(t_node *current_node, char **result, int j_temp)
{
	current_node->args_count = count_args(result, current_node, j_temp);
	if (alloc_mem_for_args_arr(current_node) == 1)
		return (1);
	return (0);
}

void	find_and_add_args(t_node *current_node, char **result, int *i, int *j)
{
	if (current_node && result[*i] && current_node->args_count > 0)
		find_args(current_node, result, i, j);
}

char	*retrieve_cmd_name(t_node *node)
{
	if (!node->cmd)
		return (NULL);
	if (node->cmd_type == NON_B_IN)
		return (ft_strrchr(node->cmd, '/') + 1);
	return (node->cmd);
}

int	count_args(char **result, t_node *current_node, int j_temp)
{
	char	*cmd_name;
	int		args_count;

	args_count = 0;
	cmd_name = retrieve_cmd_name(current_node);
	current_node->args_count = 0;
	while (result[j_temp])
	{
		if (ft_strcmp(result[j_temp], "|") == 0)
			break ;
		if (condition_is_met(current_node, cmd_name, result, j_temp) == 0)
			args_count++;
		j_temp++;
	}
	return (args_count);
}

void	find_args(t_node *current_node, char **result, int *i, int *j)
{
	char	*cmd_name;

	cmd_name = retrieve_cmd_name(current_node);
	if (condition_is_met(current_node, cmd_name, result, *i) == 0)
	{
		current_node->args[*j] = ft_strdup(result[*i]);
		current_node->fcmd = ft_strjoin_free(current_node->fcmd, result[*i]);
		(*j)++;
	}
}

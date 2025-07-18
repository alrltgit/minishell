/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:13:57 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/30 17:21:07 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_file_name(t_node *current_node, char *result)
{
	t_redir	*temp;

	temp = current_node->redir_files;
	while (temp)
	{
		if (ft_strcmp(temp->file_name, result) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	check_for_echo_flag(t_node *current_node, char **result, int j_temp)
{
	int	i;
	int	first_n_found;

	i = 0;
	first_n_found = 0;
	if (ft_strcmp(current_node->cmd, "echo") == 0 && result[j_temp][0] == '-')
	{
		while (i < current_node->flags_count)
		{
			if (ft_strcmp(current_node->flags[i], "-n") == 0 && !first_n_found)
			{
				first_n_found = 1;
				i++;
				continue ;
			}
			if (ft_strcmp(current_node->flags[i], "-n") == 0 && first_n_found)
				return (0);
			i++;
		}
	}
	return (1);
}

int	condition_is_met(t_node *current_node, char **result, int j_temp)
{
	if (result[j_temp] == NULL)
		return (1);
	if (is_redir_or_pipe(result[j_temp]))
		return (1);
	if (is_cmd_name(current_node, result, j_temp))
		return (1);
	if (is_non_flag_non_file_arg(current_node, result, j_temp))
		return (0);
	if (result[j_temp][0] != '-'
		&& is_file_name(current_node, result[j_temp]) == 0)
		return (0);
	if (is_file_name(current_node, result[j_temp]) == 1)
		return (1);
	return (1);
}

int	rl_is_space(char *rl)
{
	if (!rl)
		return (1);
	while (*rl)
	{
		if (*rl != ' ' && *rl != '\t')
			return (0);
		rl++;
	}
	return (1);
}

int	alloc_mem_for_args_arr(t_node *current_node)
{
	if (current_node->args_count > 0)
	{
		current_node->args = malloc(sizeof(char *) * current_node->args_count);
		if (!current_node->args)
			return (1);
		current_node->args[current_node->args_count - 1] = NULL;
	}
	else
	{
		current_node->args = malloc(sizeof(char *));
		if (!current_node->args)
			return (1);
		current_node->args[0] = NULL;
	}
	return (0);
}

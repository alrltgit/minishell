/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:16:49 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/30 17:30:25 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir_or_pipe(char *token)
{
	return (
		ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, ">") == 0
		|| ft_strcmp(token, "<<") == 0
		|| ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "|") == 0
	);
}

int	is_cmd_name(t_node *current_node, char **result, int j_temp)
{
	if (current_node->cmd_args_count == 0 && j_temp != 1)
	{
		if (ft_strcmp(retrieve_cmd_name(current_node), result[j_temp]) == 0)
		{
			current_node->cmd_args_count = 1;
			return (1);
		}
	}
	return (0);
}

int	is_non_flag_non_file_arg(t_node *current_node, char **result, int j_temp)
{
	if (current_node->cmd_args_count != 0
		&& result[j_temp][0] != '-'
		&& is_file_name(current_node, result[j_temp]) == 0)
	{
		current_node->cmd_args_count++;
		return (1);
	}
	return (0);
}

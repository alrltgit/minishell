/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:13:57 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/13 13:29:02 by hceviz           ###   ########.fr       */
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

int	condition_is_met(t_node *current_node,
	char *cmd_name, char **result, int j_temp)
{
	if (result[j_temp] == NULL)
		return (1);
	if (ft_strcmp(result[j_temp], "<") == 0
		|| ft_strcmp(result[j_temp], ">") == 0
		|| ft_strcmp(result[j_temp], "<<") == 0
		|| ft_strcmp(result[j_temp], ">>") == 0)
		return (1);
	if ((cmd_name == NULL && result[j_temp][0] != '-'
		&& is_file_name(current_node, result[j_temp]) == 0
		&& is_file_name(current_node, result[j_temp]) == 0)
	|| (cmd_name != NULL && ft_strcmp(result[j_temp], cmd_name) != 0
		&& result[j_temp][0] != '-'
		&& is_file_name(current_node, result[j_temp]) == 0))
	{
		return (0);
	}
	return (1);
}

int	rl_is_space(char *rl)
{
	char	*temp;

	temp = rl;
	while (*temp)
	{
		if (*temp != 32)
			return (1);
		temp++;
	}
	return (0);
}

int	alloc_mem_for_args_arr(t_node *current_node)
{
	if (current_node->args_count > 0)
	{
		current_node->args = malloc(sizeof(char *) * current_node->args_count);
		if (!current_node->args)
			return (1);
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

// char	*is_empty_quote(char **res)

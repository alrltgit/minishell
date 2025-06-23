/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:13:57 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/22 11:10:04 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <ctype.h>

int	handle_pipe_and_move(t_node **current_node, char **result, int *i, int *j)
{
	(*current_node)->cmd_idx = *i + 1;
	*j = 0;
	if (handle_pipe(current_node, result, *i, (*current_node)->cmd_idx) == 1)
		return (1);
	(*i)++;
	return (0);
}

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

int check_for_echo_flag(t_node *current_node, char **result, int j_temp)
{
	int i;
	int first_n_found;

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
				return (0); // treat as an argument
			i++;
		}
	}
	return (1); // skip as a flag
}

int	condition_is_met(t_node *current_node, char **result, int j_temp)
{
	if (result[j_temp] == NULL)
		return (1);
	if (ft_strcmp(result[j_temp], "<") == 0
		|| ft_strcmp(result[j_temp], ">") == 0
		|| ft_strcmp(result[j_temp], "<<") == 0
		|| ft_strcmp(result[j_temp], ">>") == 0
		|| ft_strcmp(result[j_temp], "|") == 0)
		return (1);
	if (ft_strcmp(retrieve_cmd_name(current_node), result[j_temp]) == 0)
		return (1);
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

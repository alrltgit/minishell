/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:43:30 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/03 12:40:29 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*retrieve_cmd_name(t_node *node)
{
	if (!node->cmd)
		return (NULL);
	if (node->cmd_type == NON_B_IN)
		return (ft_strrchr(node->cmd, '/') + 1);
	return (node->cmd);
}

int alloc_mem_for_args_arr(t_node *current_node)
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
		{
			break ;	
		}
		if (condition_is_met(cmd_name, result, j_temp) == 0)
			args_count++;	
		j_temp++;
	}
	return (args_count);
}

void	find_args(t_node *current_node, char **result, int *i, int *j)
{
	char	*cmd_name;

	cmd_name = retrieve_cmd_name(current_node);
	if (condition_is_met(cmd_name, result, *i) == 0)
	{
		current_node->args[*j] = ft_strdup(result[*i]);
		current_node->fcmd = ft_strjoin_free(current_node->fcmd, result[*i]);
		(*j)++;
	}
}

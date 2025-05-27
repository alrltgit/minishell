/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:43:30 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/27 19:53:14 by apple            ###   ########.fr       */
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
			printf("in_break\n");
			break ;	
		}
		// printf("result[i]: %s\n", result[i]);
		// printf("cmd_name: %s\n", cmd_name);
		if (condition_is_met(current_node, cmd_name, result, j_temp) == 0)
		{
			printf("in\n");
			args_count++;	
		}
		j_temp++;
	}
	return (args_count);
}

void	find_args(t_node *current_node, char **result, int *i, int *j)
{
	char	*cmd_name;

	cmd_name = retrieve_cmd_name(current_node);
	// printf("cmd_name: %s", cmd_name);
	// printf("result[i]: %s\n", result[*i]);
	if (condition_is_met(current_node, cmd_name, result, *i) == 0)
	{
		current_node->args[*j] = ft_strdup(result[*i]);
		(*j)++;
	}
}

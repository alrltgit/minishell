/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:43:30 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/26 16:28:37 by apple            ###   ########.fr       */
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

int	count_args_inside_loop(char **result, t_node *current_node, int *i)
{
	int		args_count;
	int		temp_i;
	char	*cmd_name;

	temp_i = *i;
	args_count = 0;
	cmd_name = retrieve_cmd_name(current_node);
	current_node->args_count = 0;
	while (result[temp_i])
	{
		if (is_operator(result[temp_i]))
			break ;
		if (ft_strcmp(result[temp_i], cmd_name) != 0
			&& result[temp_i][0] != '-')
			args_count++;
		temp_i++;
	}
	return (args_count);
}

int	count_args(char **result, t_node *current_node)
{
	char	*cmd_name;
	int		i;
	int		args_count;

	i = 0;
	args_count = 0;
	cmd_name = retrieve_cmd_name(current_node);
	current_node->args_count = 0;
	while (result[i])
	{
		if (is_operator(result[i]) == 0)
		{
			printf("in\n");
			break ;	
		}
		if (ft_strcmp(result[i], cmd_name) != 0 && result[i][0] != '-')
			args_count++;
		i++;
	}
	return (args_count);
}

void	find_args(t_node *current_node, char **result, int *i, int *j)
{
	char	*cmd_name;

	cmd_name = retrieve_cmd_name(current_node);
	printf("cmd_name: %s", cmd_name);
	printf("result[i]: %s\n", result[*i]);
	if ((cmd_name == NULL && result[*i][0] != '-') || (ft_strcmp(result[*i], cmd_name) != 0 && result[*i][0] != '-'))
	{
		current_node->args[*j] = ft_strdup(result[*i]);
		(*j)++;
	}
}

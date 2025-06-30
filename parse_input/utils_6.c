/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:02:45 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/30 17:27:12 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_and_prepare(char *rl, t_shell *shll, char ***result, t_node **unit)
{
	char	*check;

	check_for_empty_line(rl);
	*result = split_args(rl);
	*unit = create_unit(shll);
	(*unit)->shell = shll;
	shll->cmds = *unit;
	check = process_exp(*result, *unit);
	if (check != NULL)
	{
		set_error_status(check, *unit);
		free_linked_list(*unit);
		free_double((void **)*result);
		return (1);
	}
	return (0);
}

int	get_echo_args_start(char **result)
{
	int	j_temp;

	j_temp = 1;
	if (ft_strcmp(result[0], "echo") == 0)
	{
		while (result[j_temp] && ft_strcmp(result[j_temp], "-n") == 0)
			j_temp++;
	}
	return (j_temp);
}

void	add_args_loop(char **result, t_node **unit, int i, int j)
{
	int		k;
	t_node	*current_node;

	current_node = *unit;
	k = i;
	while (result[i])
	{
		if (ft_strcmp(result[i], "|") == 0)
		{
			current_node->cmd_args_count = 0;
			if (handle_pipe_and_move(&current_node, result, &i, &j) == 1)
				break ;
			continue ;
		}
		if (ft_strcmp(result[k], "-n") == 0)
		{
			while (result[k] && ft_strcmp(result[k], "-n") == 0)
			{
				k++;
				i++;
			}
		}
		find_and_add_args(current_node, result, i, &j);
		i++;
	}
}

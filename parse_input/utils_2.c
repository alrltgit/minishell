/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:52:11 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/09 20:51:01 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quotes_in_extract_token(const char *str, int *i,
		int *single_q, int *double_q)
{
	if (str[*i] == '\'' && !(*double_q))
		*single_q = !(*single_q);
	else if (str[*i] == '"' && !(*single_q))
		*double_q = !(*double_q);
}

void	go_to_execute(t_node *unit)
{
	if (unit->is_pipe)
		create_pipe(unit);
	else
	{
		if (unit->cmd_type == B_IN)
			execute_builtin(unit);
		else if (unit->cmd_type == NON_B_IN)
			execute_other(unit);
	}
}

int	handle_pipe(t_node **current_node, char **result, int i)
{
	*current_node = (*current_node)->next;
	if (!*current_node)
		return (1);
	(*current_node)->args_count = count_args(result, *current_node, i + 1);
	if (alloc_mem_for_args_arr(*current_node) == 1)
		return (1);
	if (!(*current_node)->args)
		return (1);
	return (0);
}

char	**get_path(void)
{
	char	*path;
	char	**paths;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

int	is_valid_command(t_node *current_node, char *rl)
{
	if (current_node->cmd == NULL)
	{
		ft_putstr_fd(ft_strcat(rl, ": command not found\n"), 2);
		return (1);
	}
	return (0);
}

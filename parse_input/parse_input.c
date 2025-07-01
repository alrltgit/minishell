/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/07/01 18:50:47 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_redir_heredoc(t_node *current_node, char **result, int *j)
{
	if (ft_strcmp(result[*j], "<") == 0)
		return (is_input_redir(current_node, result, j));
	else if (ft_strcmp(result[*j], ">") == 0)
		return (is_output_redir(current_node, result, j));
	else if (ft_strcmp(result[*j], "<<") == 0)
		return (is_heredoc_redir(current_node, result, j));
	else if (ft_strcmp(result[*j], ">>") == 0)
		return (is_append_redir(current_node, result, j));
	return (0);
}

int	check_for_cmd_flags(t_node *current_node, char *result, int *i)
{
	if (current_node->cmd_is_found == 0)
		current_node->cmd_type = find_command_path(result, current_node);
	if (current_node->cmd_type > 2)
	{
		current_node->cmd = NULL;
		return (1);
	}
	if (current_node->flags_count > 0)
		find_flags(result, current_node, i);
	return (0);
}

int	add_cmds_flags_to_linked_list(char **result, t_node **unit)
{
	t_node	*current_node;
	int		i;
	int		j;
	int		j_temp;

	current_node = *unit;
	j = 0;
	j_temp = j;
	current_node->flags_count = count_flags(result, j_temp);
	if (alloc_mem_for_flags_arr(current_node) == 1)
		return (1);
	i = 0;
	while (result[j])
	{
		if (check_for_pipe(&current_node, result, &i, &j) == 1)
			return (1);
		if (check_for_redir_heredoc(current_node, result, &j) == 1)
			return (1);
		if (check_for_cmd_flags(current_node, result[j], &i) == 1)
			return (1);
		j++;
	}
	return (0);
}

void	add_args_to_linked_list(char **result, t_node **unit)
{
	int		i;
	int		j;
	int		j_temp;
	t_node	*current_node;

	i = 1;
	j = 0;
	j_temp = get_echo_args_start(result);
	current_node = *unit;
	if (allocate_args_memory(current_node, result, j_temp) == 1)
		return ;
	add_args_loop(result, unit, i, j);
}

void	read_the_input(char *rl, t_shell *shll)
{
	char	**result;
	t_node	*unit;
	t_node	*temp;

	if (parse_and_prepare(rl, shll, &result, &unit))
		return ;
	temp = unit;
	if (add_cmds_flags_to_linked_list(result, &temp) == 1)
	{
		free_linked_list(unit);
		free_double((void **)result);
		return ;
	}
	if (result[0])
		add_args_to_linked_list(result, &temp);
	temp = unit;
	if (result[0])
		go_to_execute(result, temp);
	free_double((void **)result);
	free_linked_list(unit);
}

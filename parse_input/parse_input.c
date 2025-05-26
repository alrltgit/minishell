/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/26 12:55:46 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_cmds_flags_to_linked_list(char **result, t_node **unit)
{
	t_node	*current_node;
	int		i;
	int		j;
	int		j_temp;
	int		cmd_is_found;

	cmd_is_found = 0;
	current_node = *unit;
	j = 0;
	j_temp = j;
	current_node->flags_count = count_flags(result, j_temp);
	if (current_node->flags_count > 0)
	{
		current_node->flags = malloc(sizeof(char *)
				* (current_node->flags_count + 1));
		if (!current_node->flags)
			return (1);
	}
	else
	{
		current_node->flags = malloc(sizeof(char *));
		if (!current_node->flags)
			return (1);
		current_node->flags[0] = NULL;
	}
	i = 0;
	if (ft_strcmp(result[j], "<") == 0)
	{
		current_node->stdin_redirect = 1;
		current_node->file_name = ft_strdup(result[++j]);
		j++;
	}
	while (result[j])
	{
		if (ft_strcmp(result[j], "|") == 0)
		{
			current_node->is_pipe = 1;
			current_node = add_unit_to_end(unit);
			j_temp = j;
			j_temp++;
			current_node->flags_count = count_flags(result, j_temp);
			if (current_node->flags_count > 0)
			{
				current_node->flags = malloc(sizeof(char *)
						* (current_node->flags_count + 1));
				if (!current_node->flags)
					return (1);
			}
			else
			{
				current_node->flags = malloc(sizeof(char *));
				if (!current_node->flags)
					return (1);
				current_node->flags[0] = NULL;
			}
			i = 0;
			cmd_is_found = 0;
			j++;
		}
		if (cmd_is_found == 0)
			current_node->cmd_type = find_command_path(result[j],
					current_node, &cmd_is_found);
		if (cmd_is_found == 0)
		{
			printf("%s: command not found\n", result[j]);
			return (1);
		}
		if (current_node->flags_count > 0)
			find_flags(result[j], current_node, &i);
		j++;
	}
	return (0);
}

void	add_args_to_linked_list(char **result, t_node **unit)
{
	int		i;
	int		j;
	t_node	*current_node;

	j = 0;
	current_node = *unit;
	current_node->args_count = count_args(result, current_node);
	current_node->args = malloc(sizeof(char *) * current_node->args_count + 1);
	i = 0;
	while (result[i])
	{
		if (ft_strcmp(result[i], "|") == 0)
		{
			j = 0;
			current_node = current_node->next;
			if (!current_node)
				break ;
			current_node->args_count = count_args_inside_loop(result,
					current_node, &i);
			current_node->args = malloc(sizeof(char *)
					* current_node->args_count + 1);
			if (!current_node->args)
				return ;
			i++;
		}
		if (current_node && result[i])
			find_args(current_node, result, &i, &j);
		i++;
	}
}

/* void read_the_input(char *rl, t_shell *shll)
{
    char	**result;
    t_node 	*unit;
    t_node 	*temp;
	
    char **result;
    t_node *unit;
    t_node *temp;

	if (ft_strcmp(rl, "") == 0 || rl_is_space(rl) == 0)
	{
		// rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
		return ;
	}
    result = split_args(rl);
    unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
	temp = unit;
	add_cmds_flags_to_linked_list(result, &temp);
	add_args_to_linked_list(result, &temp);
	if (temp->cmd_type == B_IN)
	{
		execute_builtin(temp);
		printf("builtin cmd-> %s\n", temp->cmd);
	}
	else if (temp->cmd_type == NON_B_IN)
	{
		execute_other(temp);
		printf("cmd-> %s\n", temp->cmd);
	}
	else
	{
		ft_printf("%s", result[0]);
		printf("cmd-> %s\n", temp->cmd);
		ft_putstr_fd(" : command not found\n", 2);
	}
    free(result);
} */

void	read_the_input(char *rl, t_shell *shll)
{
	char	**result;
	t_node	*unit;
	t_node	*temp;

	if (ft_strcmp(rl, "") == 0 || rl_is_space(rl) == 0)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
		return ;
	}
	result = split_args(rl);
	unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
	temp = unit;
	/* if (add_cmds_flags_to_linked_list(result, &temp) == 1)
		return ; */
	add_cmds_flags_to_linked_list(result, &temp);
	add_args_to_linked_list(result, &temp);
	//print_node(unit);
	process_exp(unit);
	// perfect(unit, &unit->args[0]);
	if (unit->is_pipe)
		create_pipe(unit);
	else
	{
		if (unit->cmd_type == B_IN)
			execute_builtin(unit);
		else if (unit->cmd_type == NON_B_IN)
			execute_other(unit);
		else
		{
			ft_printf("%s", result[0]);
			ft_putstr_fd(" : command not found\n", 2);
		}
	}
	free_arr(result);
}

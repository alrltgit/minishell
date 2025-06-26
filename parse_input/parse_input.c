/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/06/26 15:40:08 by alraltse         ###   ########.fr       */
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
	printf("fcmdddd -> %s\n", current_node->fcmd);
	printf("before cmd is found-> %d\n------------------\n", current_node->cmd_is_found);
	if (current_node->cmd_is_found == 0)
		current_node->cmd_type = find_command_path(result, current_node);
	printf("after cmd is found-> %d\n", current_node->cmd_is_found);
	if (current_node->cmd_type > 2)
	{
		current_node->cmd = NULL;
		return (1);
	}
	printf("current_node->flags_count: %d\n-----------------\n", current_node->flags_count);
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
	printf("current_node->flags_count: %d\n", current_node->flags_count);
	if (alloc_mem_for_flags_arr(current_node) == 1)
		return (1);
	i = 0;
	while (result[j])
	{
		/* if (fake_perfect(*unit, result[j]))
			return (1); */
		if (check_for_pipe(&current_node, result, &i, &j) == 1)
			return (1);
		if (check_for_redir_heredoc(current_node, result, &j) == 1)
			return (1);
		if (check_for_cmd_flags(current_node, result[j], &i) == 1)
			return (1);
		//! if it is not in if block, even it executes incorretly -$PATH echo abc



		/* if (current_node->is_pipe == 1)
		{
			++j;
			continue;
		}
		int res = check_for_cmd_flags(current_node, result[j], &i);
		if (res == 1)
			return (1); */
		/* if (res == 1 && current_node->is_pipe == 0)
			return (1); */
		j++;
	}
	return (0);
}

void	add_args_to_linked_list(char **result, t_node **unit)
{
	int		i;
	int		j;
	int		j_temp;
	// int 	r;
	t_node	*current_node;

	j = 0;
	j_temp = j + 1;
	current_node = *unit;
	if (ft_strcmp(result[0], "echo") == 0)
	{
		j_temp = 1;
		while (ft_strcmp(result[j_temp], "-n") == 0)
		{
			j_temp++;
		}
	}
	if (allocate_args_memory(current_node, result, j_temp) == 1)
		return ;
	i = 1;
	int k = i;
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
			while (ft_strcmp(result[k], "-n") == 0)
			{
				k++;
				i++;
			}
		}
		find_and_add_args(current_node, result, i, &j);
		i++;
	}
}

void read_the_input(char *rl, t_shell *shll)
{
    char	**result;
    t_node 	*unit;
    t_node 	*temp;
	char	*check;

	check_for_empty_line(rl);
	result = split_args(rl);
	unit = create_unit(shll);
	unit->shell = shll;
	shll->cmds = unit;
	//unit->shell->exit_code = 0;
	check = process_exp(result, unit);
	// printf("check-> %s\n", check);
	// printf("result[0]: %s\n", result[0]);
	if (check != NULL)
	{
		set_error_status(check, unit);
		/* if (ft_strcmp(check, "") == 0)
		{
			printf("\e[0;31mminishell: : command not found222\n");
			free_arr(result);
			return ;
		} */
		free_linked_list(unit);
		free_double((void **)result);
		return ;
	}
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
    // int i;
    // t_redir *r;
    // while (temp)
    // {
	// 	printf("temp->cmd_args_count: %d\n", temp->cmd_args_count);
	// 	printf("temp->args_count: %d\n", temp->args_count);
    //     printf("temp->cmd: %s\n", temp->cmd);
    //     i = 0;
    //     while (i < temp->flags_count)
    //     {
    //         printf("temp->flags[%d]: %s\n", i, temp->flags[i]);
    //         i++;
    //     }
    //     i = 0;
    //     while (i < temp->args_count)
    //     {
    //         printf("temp->args[%d]: %s\n", i, temp->args[i]);
    //         i++;
    //     }
    //     r = temp->redir_files;
    //     while (r)
    //     {
    //         printf("temp->redir_files->file_name: %s\n", r->file_name);
    //         r = r->next;
    //     }
    //     temp = temp->next;
    // }
	if (result[0])
		go_to_execute(result, temp);
	printf("exit code at the bottom of parse-> %d", shll->exit_code);
	free_double((void **)result);
	free_linked_list(unit);
}

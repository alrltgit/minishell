/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/06/22 11:50:19 by hceviz           ###   ########.fr       */
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
		/* if (fake_perfect(*unit, result[j]))
			return (1); */
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

	j = 0;
	j_temp = j + 1;
	current_node = *unit;
	if (allocate_args_memory(current_node, result, j_temp) == 1)
		return ;
	i = 1;
	while (result[i])
	{
		if (ft_strcmp(result[i], "|") == 0)
		{
			if (handle_pipe_and_move(&current_node, result, &i, &j) == 1)
				break ;
			continue ;
		}
		find_and_add_args(current_node, result, i, &j);
		i++;
	}
}

/* void read_the_input(char *rl, t_shell *shll)
{
    char	**result;
    t_node 	*unit;
    t_node 	*temp;
	char	*check;

	check_for_empty_line(rl);
	result = split_args(rl);
	unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
	
	//add check for "" and ''
	//print_node(unit);
	check = process_exp(result, unit);
	if (check != NULL)
	{
		if (ft_strcmp(check, "") == 0)
		{
			free_arr(result);
			return;
		}
		printf("\e[0;31mminishell: %s: syntax error\n", check);
		shll->exit_code = 127;
		free_arr(result);
		return ;
	}
	temp = unit;
	if (add_cmds_flags_to_linked_list(result, &temp) == 1)
		return ;
	add_args_to_linked_list(result, &temp);
	go_to_execute(unit);
	free_arr(result);
} */

void read_the_input(char *rl, t_shell *shll)
{
    char	**result;
    t_node 	*unit;
    t_node 	*temp;
	char	*check;

	check_for_empty_line(rl);
	result = split_args(rl);
	unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
	//unit->shell->exit_code = 0;
	check = process_exp(result, unit);
	printf("check-> %s\n", check);
	if (check != NULL)
	{
		if (ft_strcmp(check, "") && fake_perfect(check))
			set_error_status(" ", unit);
		else
			set_error_status(check, unit);
		/* if (check[0] && ((check[0] == '"' && check[ft_strlen(check) - 1] == '\'')
			|| (check[0] == '\'' && check[ft_strlen(check) - 1] == '"')))
		{
			printf("\e[0;31mminishell: syntax error\n");
			free_arr(result);
			return ;
		} */
			
		/* if (ft_strcmp(check, "") == 0)
		{
			printf("\e[0;31mminishell: : command not found222\n");
			free_arr(result);
			return ;
		} */
		//shll->exit_code = 127;
		free_arr(result);
		return ;
	}
	temp = unit;
	if (add_cmds_flags_to_linked_list(result, &temp) == 1 || temp->cmd == NULL)
		return ;
	add_args_to_linked_list(result, &temp);
	print_node(unit);
	/* temp = unit;
    int i;
    t_redir *r;
    while (temp)
    {
        printf("temp->cmd: %s\n", temp->cmd);
        i = 0;
        while (i < temp->flags_count)
        {
            printf("temp->flags[%d]: %s\n", i, temp->flags[i]);
            i++;
        }
        i = 0;
        while (i < temp->args_count)
        {
            printf("temp->args[%d]: %s\n", i, temp->args[i]);
            i++;
        }
        r = temp->redir_files;
        while (r)
        {
            printf("temp->redir_files->file_name: %s\n", r->file_name);
            r = r->next;
        }
        temp = temp->next;
    } */
	go_to_execute(unit);
	free_arr(result);
}

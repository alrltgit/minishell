/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/06/07 21:11:34 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_for_redir_heredoc(t_node *current_node, char **result, int *j)
{
    if (ft_strcmp(result[*j], "<") == 0)
    {
        if (result[*j + 1] == NULL)
            return (1);
        add_new_file(&current_node->redir_files, result[*j + 1]); 
        current_node->redir_files->type->stdin_redir = 1;
        printf("current_node->redir_files->type->stdin_redir: %d\n", current_node->redir_files->type->stdin_redir);
        (*j)++;
    }
    else if (ft_strcmp(result[*j], ">") == 0)
    {
        if (result[*j + 1] == NULL)
            return (1);
        add_new_file(&current_node->redir_files, result[*j + 1]);
        current_node->redir_files->type->stdout_redir = 1;
        printf("current_node->redir_files->type->stdout_redir: %d\n", current_node->redir_files->type->stdout_redir);
        (*j)++;
    }
    else if (ft_strcmp(result[*j], "<<") == 0)
    {
        if (result[*j + 1] == NULL)
            return (1);
        add_new_file(&current_node->redir_files, result[*j + 1]);
        current_node->redir_files->type->heredoc_redir = 1;
        printf("current_node->redir_files->type->heredoc_redir: %d\n", current_node->redir_files->type->heredoc_redir);
        (*j)++;
    }
    else if (ft_strcmp(result[*j], ">>") == 0)
    {
        if (result[*j + 1] == NULL)
            return (1);
        add_new_file(&current_node->redir_files, result[*j + 1]);
        current_node->redir_files->type->append_redir = 1;
        printf("current_node->redir_files->type->append_redir: %d\n", current_node->redir_files->type->append_redir);
        (*j)++;
    }
    return (0);
}

int add_cmds_flags_to_linked_list(char **result, t_node **unit)
{
    t_node *current_node;
    int i;
    int j;
    int c;
    int j_temp;

    current_node = *unit;
    j = 0;
    j_temp = j;
    current_node->flags_count = count_flags(result, j_temp);
    if (alloc_mem_for_flags_arr(current_node) == 1)
        return (1);
    i = 0;
    c = 0;
    while (result[j])
    {
        if (check_for_pipe(&current_node, unit, result, &i, &j, &c) == 1)
            return (1);
        if (check_for_redir_heredoc(current_node, result, &j) == 1)
            return (1);
        if (current_node->cmd_is_found == 0)
            current_node->cmd_type = find_command_path(result[j], current_node);
        if (current_node->cmd_type > 2)
        {
            current_node->cmd = NULL;
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
    int     j_temp;
	t_node	*current_node;

	j = 0;
    j_temp = j;
	current_node = *unit;
	current_node->args_count = count_args(result, current_node, j_temp);
    if (alloc_mem_for_args_arr(current_node) == 1)
    {
        return ;
    }
	i = 0;
	while (result[i])
	{
		if (ft_strcmp(result[i], "|") == 0)
		{
			j = 0;
			current_node = current_node->next;
			if (!current_node)
            {
                break ;
            }
			current_node->args_count = count_args(result,
					current_node, i + 1);
            if (alloc_mem_for_args_arr(current_node) == 1)
                return ;
			if (!current_node->args)
				return ;
			i++;
            continue ;
		}
		if (current_node && result[i] && current_node->args_count > 0)
			find_args(current_node, result, &i, &j);
		i++;
	}
}

void read_the_input(char *rl, t_shell *shll)
{
    char	**result;
    t_node 	*unit;
    t_node 	*temp;

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
    process_exp(result, unit);
	temp = unit;
	if (add_cmds_flags_to_linked_list(result, &temp) == 1)
        return ;
	add_args_to_linked_list(result, &temp);
    temp = unit;
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
    }
	if (unit->is_pipe)
    {
        create_pipe(unit);
    }
	else
	{
		if (unit->cmd_type == B_IN)
			execute_builtin(unit);
		else if (unit->cmd_type == NON_B_IN)
			execute_other(unit);
	}
	free_arr(result);
}

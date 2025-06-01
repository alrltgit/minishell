/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/06/01 12:24:27 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_quotes(char *str)
{
	int	i;
	int	sq;
	int	dq;
	char	*temp;

	i = -1;
	sq = 0;
	dq = 0;
	temp = NULL;
	// "'"$PATH"'"
	// printf("BEFORE HANDLING QUOTES -> %s\n", str);
	while (str[++i])
	{
		if (str[i] == '\'' && dq == 0)
		{
			sq = 1 - sq;
			while (str[++i])
			{
				if (str[i] == '\'')
					continue;
				temp = update_str(temp, str[i]);
			}
		}
		if (str[i] == '"' && sq == 0)
		{
			dq = 2 - dq;
			while (str[i++])
			{
				if (str[i] == '"')
					continue;
				temp = update_str(temp, str[i]);
			}
		}
		else
			temp = update_str(temp, str[i]);
	}
	// printf("AFTER HANDLING QUOTES -> %s\n", temp);
	return (temp);
}

int alloc_mem_for_flags_arr(t_node *current_node)
{
    if (current_node->flags_count > 0)
    {
        current_node->flags = malloc(sizeof(char *) * (current_node->flags_count + 1));
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
    return (0);
}

t_redir *add_new_file(t_redir **head)
{
    t_redir *new_node;
    t_redir *temp;

    new_node = malloc(sizeof(t_redir));
    if (!new_node)
        return (NULL);
    
    // 💥 Initialize ALL members
    new_node->file_name = NULL;
    new_node->next = NULL;

    if (!*head)
    {
        *head = new_node;
        return (new_node);
    }

    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;

    return (new_node);
}


int check_for_redir(t_node *current_node, char **result, int *j)
{
    t_redir *new_redir;
    
    if (ft_strcmp(result[*j], "<") == 0)
    {
        current_node->stdin_redirect = 1;
        new_redir = add_new_file(&current_node->redir_files);
        if (!new_redir)
            return (1);
        new_redir->file_name = ft_strdup(result[*j + 1]);
        if (!new_redir->file_name)
            return (1);
        if (access(new_redir->file_name, F_OK) != 0)
        {
            printf("%s: No such file or directory.\n", new_redir->file_name);
            return (1);
        }
        if (access(new_redir->file_name, R_OK) != 0)
        {
            printf("%s: Permission denied.\n", new_redir->file_name);
            return (1);
        }
        (*j)++;
    }
    return (0);
}

int check_for_pipe(t_node **current_node, t_node **unit, char **result, int *i, int *j, int *c)
{
    int j_temp;

    if (ft_strcmp(result[*j], "|") == 0)
    {
        (*current_node)->is_pipe = 1;
        *current_node = add_unit_to_end(unit);
        j_temp = *j + 1;
        
        if (!result[j_temp])
            return (1);
        
        (*current_node)->flags_count = count_flags(result, j_temp);
        (*current_node)->vars_count = count_variables(result, &j_temp);
        if (alloc_mem_for_flags_arr(*current_node) == 1)
            return (1);
        if (alloc_mem_for_vars_arr(*current_node) == 1)
            return (1);
        *i = 0;
        *c = 0;
        (*current_node)->cmd_is_found = 0;
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
    current_node->vars_count = count_variables(result, &j);
    if (alloc_mem_for_flags_arr(current_node) == 1)
        return (1);
    if (alloc_mem_for_vars_arr(current_node) == 1)
        return (1);
    i = 0;
    c = 0;
    while (result[j])
    {
        if (check_for_pipe(&current_node, unit, result, &i, &j, &c) == 1)
            return (1);
        if (check_for_redir(current_node, result, &j) == 1)
            return (1);
        if (current_node->cmd_is_found == 0)
            current_node->cmd_type = find_command_path(result[j], current_node);
        if (current_node->cmd_is_found == 0)
        {
            current_node->cmd = NULL;
        //     printf("%s: command not found\n", result[j]);
        //     return (1);
        }
        if (current_node->flags_count > 0)
            find_flags(result[j], current_node, &i);
        if (current_node->vars_count > 0)
            find_vars(result[j], current_node, &c);
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
		if (current_node && result[i])
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
	temp = unit;
	/* if (add_cmds_flags_to_linked_list(result, &temp) == 1)
		return ; */
    
    add_cmds_flags_to_linked_list(result, &temp);
    //temp = unit;
	add_args_to_linked_list(result, &temp);
    // temp = unit;
    // int i;
    // while (temp)
    // {
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
    //     i = 0;
    //     while (i < temp->vars_count)
    //     {
    //         printf("temp->vars[%d]: %s\n", i, temp->vars[i]);
    //         i++;
    //     }
    //     i = 0;
    //     while (temp->redir_files)
    //     {
    //         printf("temp->redir_files->file_name: %s\n", temp->redir_files->file_name);
    //         temp->redir_files = temp->redir_files->next;
    //     }
    //     temp = temp->next;
    // }
	// print_node(unit);
    process_exp(unit);
	// perfect(unit, &unit->vars[0]);
	if (unit->is_pipe)
		create_pipe(unit);
	else
	{
		if (unit->cmd_type == B_IN)
			execute_builtin(unit);
		else if (unit->cmd_type == NON_B_IN)
			execute_other(unit);
		// else
		// {
		// 	ft_printf("%s", result[0]);
		// 	ft_putstr_fd(" : command not found\n", 2);
		// }
	}
	free_arr(result);
}

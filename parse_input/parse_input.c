/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/12 12:21:16 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void add_cmds_flags_to_linked_list(char **result, t_node **unit)
{
    t_node *current_node;
    int i;
    int j;
    int cmd_is_found;

    cmd_is_found = 0;
    current_node = *unit;
    current_node->flags_count = count_flags(result);
    current_node->flags = malloc(sizeof(char *) * current_node->flags_count + 1);
    if (!current_node->flags)
        return ;
    i = 0;
    j = 0;
    if (ft_strcmp(result[j], "|") == 0 || ft_strcmp(result[j], ">>") == 0
        || ft_strcmp(result[j], "<<") == 0)
        j++;
    while (result[j])
    {
        if (ft_strcmp(result[j], "|") == 0 || ft_strcmp(result[j], ">>") == 0
            || ft_strcmp(result[j], "<<") == 0)
        {
            current_node = add_unit_to_end(unit);
            current_node->flags_count = count_flags(result);
            current_node->flags = malloc(sizeof(char *) * current_node->flags_count + 1);
            if (!current_node->flags)
                return ;
            i = 0;
            cmd_is_found = 0;
            j++;
            continue ;
        }
        if (cmd_is_found == 0)
            current_node->cmd_type = find_command_path(result[j], current_node, &cmd_is_found);
        find_flags(result[j], current_node, &i);
        j++;
    }
    current_node->flags[i] = NULL;
}

void add_args_to_linked_list(char **result, t_node **unit)
{
    int i;
    int j;
    t_node *current_node;

    j = 0;
    current_node = *unit;
    current_node->args_count = count_args(result, current_node);
    current_node->args = malloc(sizeof(char *) * current_node->args_count + 1);
    i = 0;
    if (ft_strcmp(result[i], "|") == 0 || ft_strcmp(result[i], "<") == 0
    || ft_strcmp(result[i], ">") == 0 || ft_strcmp(result[i], ">>") == 0
    || ft_strcmp(result[i], "<<") == 0)
        i++;
    while (result[i])
    {
        if (ft_strcmp(result[i], "|") == 0 || ft_strcmp(result[i], "<") == 0
            || ft_strcmp(result[i], ">") == 0 || ft_strcmp(result[i], ">>") == 0
            || ft_strcmp(result[i], "<<") == 0)
        {
            i++;
            j = 0;
            current_node = current_node->next;
            if (!current_node)
                break ;
            current_node->args_count = count_args_inside_loop(result, current_node, &i);
			printf("current_node->args_count: %d\n", current_node->args_count);
            current_node->args = malloc(sizeof(char *) * current_node->args_count + 1);
            if (!current_node->args)
                return ;
        }
        if (current_node && result[i])
            find_args(current_node, result, &i, &j);
        i++;
    }
    current_node->args[j] = NULL;
}

void read_the_input(char *rl, t_shell *shll)
{
    char **result;
    t_node *unit;
    t_node *temp;
    
	if (is_only_wspc_empty(rl))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		return ;
	}
    result = split_args(rl);
    unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
	temp = unit;
	//Iterate temp to pass all nodes
    add_cmds_flags_to_linked_list(result, &temp);
    if (temp->cmd_type == B_IN)
    {
		add_args_to_linked_list(result, &temp);
		// execute_builtin(temp);
    }
    else if (temp->cmd_type == NON_B_IN)
	{
		add_args_to_linked_list(result, &temp);
		// execute_other(temp);
	}
	else
	{
		//command is not valid case
	}
   /*  t_node *temp = unit;
    int i;
    int j;
    while (temp)
    {
        printf("temp->cmd: %s\n", temp->cmd);
        i = 0;
        while (temp->flags[i])
        {
            printf("temp->flags[%d]: %s\n", i, temp->flags[i]);
            i++;
        }
        j = 0;
        while (temp->args[j])
        {
            printf("temp->args[%d]: %s\n", j, temp->args[j]);
            j++;
        }
        temp = temp->next;
    } */
    free(result);
}
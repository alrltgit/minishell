/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/10 16:01:25 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_valid_command(t_node *current_node, char *rl)
{
    if (current_node->cmd == NULL)
    {
        ft_putstr_fd(ft_strconcat(rl, ": command not found\n"), 2);
        return (1);
    }
    return (0);
}

t_node *add_cmds_flags_to_linked_list(char **result, t_node **unit)
{
    t_node *current_node;
    int i;
    int j;
    int cmd_is_found;

    i = 0;
    j = 0;
    cmd_is_found = 0;
    current_node = *unit;
    current_node->flags_count = count_flags(result);
    current_node->flags = malloc(sizeof(char *) * current_node->flags_count + 1);
    if (!current_node->flags)
        return (NULL);
    while (result[j])
    {
        if (ft_strcmp(result[j], "|") == 0 || ft_strcmp(result[j], "<") == 0
            || ft_strcmp(result[j], ">") == 0 || ft_strcmp(result[j], ">>") == 0
            || ft_strcmp(result[j], "<<") == 0)
        {
            current_node = add_unit_to_end(unit);
            current_node->flags_count = count_flags(result);
            current_node->flags = malloc(sizeof(char *) * current_node->flags_count + 1);
            if (!current_node->flags)
                return (NULL);
            i = 0;
            cmd_is_found = 0;
            j++;
            continue ;
        }
        if (cmd_is_found == 0)
            find_command_path(result[j], current_node, &cmd_is_found);
        find_flags(result[j], current_node, &i);
        j++;
    }
    if (cmd_is_found == 0)
    {
        current_node->cmd = NULL;
        current_node->flags[i] = NULL;
    }
    // else
    //     current_node->flags[i] = NULL;
    return (current_node);
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
            current_node->args = malloc(sizeof(char *) * current_node->args_count + 1);
            if (!current_node->args)
                return ;
        }
        if (current_node && result[i])
            find_args(current_node, result, &i, &j);
        i++;
    }
    // current_node->args[j] = NULL;
}

void read_the_input(char *rl, t_shell *shll)
{
    char **result;
    t_node *unit;
    t_node *current_node;
    
    result = split_args(rl);
    unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
    current_node = add_cmds_flags_to_linked_list(result, &unit);
    if (is_valid_command(current_node, rl) == 1)
    {
        shll->errcode = 1;
        return ;
        // check if the command is a builtin.
        //if (is_builtin())
        //	execute_builtin()
        //else
        //  execute_other()
    }
    else
        add_args_to_linked_list(result, &unit);

    // print cmds, flsgs, args
    // t_node *temp = unit;
    // int i;
    // int j;
    // while (temp)
    // {
    //     printf("temp->cmd: %s\n", temp->cmd);
    //     i = 0;
    //     while (temp->flags[i])
    //     {
    //         printf("temp->flags[%d]: %s\n", i, temp->flags[i]);
    //         i++;
    //     }
    //     j = 0;
    //     while (temp->args[j])
    //     {
    //         printf("temp->args[%d]: %s\n", i, temp->args[j]);
    //         j++;
    //     }
    //     temp = temp->next;
    // }
    free(result);
}
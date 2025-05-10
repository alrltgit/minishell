/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/10 12:21:00 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void add_cmds_flags_to_linked_list(char **result, t_node **unit)
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
    printf("%d\n", current_node->flags_count);
    current_node->flags = malloc(sizeof(char *) * current_node->flags_count);
    if (!current_node->flags)
        return ;
    while (result[j])
    {
        if (ft_strcmp(result[j], "|") == 0 || ft_strcmp(result[j], "<") == 0
            || ft_strcmp(result[j], ">") == 0 || ft_strcmp(result[j], ">>") == 0
            || ft_strcmp(result[j], "<<") == 0)
        {
            current_node = add_unit_to_end(unit);
            current_node->flags_count = count_flags(result);
            current_node->flags = malloc(sizeof(char *) * current_node->flags_count);
            if (!current_node->flags)
                return ;
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
            // printf("result[i]_1: %s\n", result[i]);
            i++;
            printf("result[i]_2: %s\n", result[i]);
            j = 0;
            current_node = current_node->next;
            printf("current_node->cmd_2: %s\n", current_node->cmd);
            if (!current_node)
            {
                printf("IN\n");
                break ;
            }
            current_node->args_count = count_args_inside_loop(result, current_node, &i);
            // printf("current_node->args_count_1: %d\n", current_node->args_count);
            current_node->args = malloc(sizeof(char *) * current_node->args_count + 1);
            if (!current_node->args)
            {
                printf("Memory allocation failed.\n");
                return ;
            }
            // continue ;
        }
        printf("result[i]: %s\n", result[i]);
        if (current_node && result[i])
        {
            printf("TEST\n");
            find_args(current_node, result, &i, &j);
            printf("current_node->args[%d]: %s\n", j, current_node->args[j]);
        }
        i++;
    }
    current_node->args[j] = NULL;
}

void read_the_input(char *rl, t_shell *shll)
{
    char **result;
    t_node *unit;
    
    result = split_args(rl);
    unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
    add_cmds_flags_to_linked_list(result, &unit);
    t_node *temp = unit;
    // int i;
    // while (temp)
    // {
    //     printf("temp->cmd: %s\n", temp->cmd);
    //     // printf("unit->args_count: %d\n", unit->args_count);
    //     i = 0;
    //     while (i < 1)
    //     {
    //         printf("temp->flags[%d]: %s\n", i, temp->flags[i]);
    //         // printf("temp->args[%d]: %s\n", i, temp->args[i]);
    //         i++;
    //     }
    //     temp = temp->next;
    // }
    add_args_to_linked_list(result, &unit);
    int i;
    while (temp)
    {
        printf("temp->cmd: %s\n", temp->cmd);
        // printf("unit->args_count: %d\n", unit->args_count);
        i = 0;
        while (i < 1)
        {
            printf("temp->args[%d]: %s\n", i, temp->args[i]);
            // printf("temp->args[%d]: %s\n", i, temp->args[i]);
            i++;
        }
        temp = temp->next;
    }
    //print cmds and flags
    // int i;
    // while (shll->cmds)
    // {
    //     printf("temp->shell->cmds->cmd: %s\n", shll->cmds->cmd);
    //     i = 0;
    //     while (i < 2)
    //     {
    //         printf("temp->shell->cmds->cmd: %s\n", shll->cmds->flags[i]);
    //         i++;
    //     }
    //     shll->cmds = shll->cmds->next;
    // }
    free(result);
}
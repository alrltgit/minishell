/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/08 18:14:53 by alraltse         ###   ########.fr       */
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
            i++;
            j = 0;
            current_node = current_node->next;
            if (!current_node)
                break ;
            current_node->args_count = count_args_inside_loop(result, current_node, &i);
            current_node->args = malloc(sizeof(char *) * current_node->args_count + 1);
            continue ;
        }
        find_args(current_node, result, &i, &j);
        printf("current_node->args[%d]: %s\n", j, current_node->args[j]);
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
    int i;
    while (temp)
    {
        printf("temp->cmd: %s\n", temp->cmd);
        // printf("unit->args_count: %d\n", unit->args_count);
        i = 0;
        while (i < 1)
        {
            printf("temp->flags[%d]: %s\n", i, temp->flags[i]);
            // printf("temp->args[%d]: %s\n", i, temp->args[i]);
            i++;
        }
        temp = temp->next;
    }
    add_args_to_linked_list(result, &unit);
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
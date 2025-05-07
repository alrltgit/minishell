/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/07 13:59:01 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void add_cmds_flags_to_linked_list(char **result, t_unit **unit)
{
    t_unit *current_unit;
    int i;
    int j;
    int cmd_is_found;

    i = 0;
    j = 0;
    cmd_is_found = 0;
    current_unit = *unit;
    current_unit->data->flags_count = count_flags(result);
    current_unit->data->flags = malloc(sizeof(char *) * current_unit->data->flags_count);
    if (!current_unit->data->flags)
        return ;
    while (result[j])
    {
        if (ft_strcmp(result[j], "|") == 0 || ft_strcmp(result[j], "<") == 0
            || ft_strcmp(result[j], ">") == 0 || ft_strcmp(result[j], ">>") == 0
            || ft_strcmp(result[j], "<<") == 0)
        {
            current_unit = add_unit_to_end(unit);
            current_unit->data->flags_count = count_flags(result);
            current_unit->data->flags = malloc(sizeof(char *) * current_unit->data->flags_count);
            if (!current_unit->data->flags)
                return ;
            i = 0;
            cmd_is_found = 0;
            j++;
            continue ;
        }
        if (cmd_is_found == 0)
            find_command_path(result[j], current_unit, &cmd_is_found);
        find_flags(result[j], current_unit, &i);
        j++;
    }
}

void add_args_to_linked_list(char **result, t_unit *unit)
{
    int i;
    int j;

    unit->data->args = malloc(sizeof(char *) * unit->data->args_count);
    if (!unit->data->args)
        return ;
    i = 0;
    j = 0;
    while (result[j])
    {
        if (ft_strcmp(result[j], "|") == 0 || ft_strcmp(result[j], "<") == 0
            || ft_strcmp(result[j], ">") == 0 || ft_strcmp(result[j], ">>") == 0
            || ft_strcmp(result[j], "<<") == 0)
        {
            break ;
        }
        find_args(unit, result, &i, &j);
        j++;
    }
}

void read_the_input(char *rl)
{
    char **result;
    t_unit *unit;
    
    result = split_args(rl);
    unit = malloc(sizeof(t_unit));
    unit->data = malloc(sizeof(t_node));
    add_cmds_flags_to_linked_list(result, &unit);
    unit->data->args_count = count_args(unit, result);
    add_args_to_linked_list(result, unit);
    // int i;
    // int j;
    // while (unit)
    // {
    //     printf("unit->data->cmd: %s\n", unit->data->cmd);
    //     i = 0;
    //     while (i < unit->data->flags_count)
    //     {
    //         printf("unit->data->flags[%d]: %s\n", i, unit->data->flags[i]);
    //         i++;
    //     }
    //     // j = 0;
    //     // while (j < 1)
    //     // {
    //     //     printf("unit->data->args[%d]: %s\n", j, unit->data->args[j]);
    //     //     j++;
    //     // }
    //     unit = unit->next;
    // }
    free(result); // unit->data->cmd // unit->data->flags[i]
}
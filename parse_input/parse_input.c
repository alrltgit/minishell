/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/06 19:45:29 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void add_cmds_flags_to_linked_list(t_lexer *input, t_unit **unit)
{
    t_lexer *temp;
    t_unit *current_unit;
    int i;
    int cmd_is_found;

    i = 0;
    cmd_is_found = 0;
    temp = input;
    current_unit = *unit;
    current_unit->data->flags = malloc(sizeof(char *) * 10);
    if (!current_unit->data->flags)
        return ;
    while (temp)
    {
        if (ft_strcmp(temp->data, "|") == 0 || ft_strcmp(temp->data, "<") == 0
            || ft_strcmp(temp->data, ">") == 0 || ft_strcmp(temp->data, ">>") == 0
            || ft_strcmp(temp->data, "<<") == 0)
        {
            current_unit = add_unit_to_end(unit);
            current_unit->data->flags = malloc(sizeof(char *) * 10);
            if (!current_unit->data->flags)
                return ;
            i = 0;
            cmd_is_found = 0;
            temp = temp->next;
            continue ;
        }
        if (cmd_is_found == 0)
            find_command_path(temp->data, current_unit, &cmd_is_found);
        find_flags(temp, current_unit, &i);
        temp = temp->next;
    }
}

void add_args_to_linked_list(t_lexer *input, t_unit *unit)
{
    t_lexer *temp;
    int i;

    unit->data->args = malloc(sizeof(char *) * unit->data->args_count);
    if (!unit->data->args)
        return ;
    i = 0;
    temp = input;
    while (temp)
    {
        if (ft_strcmp(temp->data, "|") == 0 || ft_strcmp(temp->data, "<") == 0
            || ft_strcmp(temp->data, ">") == 0 || ft_strcmp(temp->data, ">>") == 0
            || ft_strcmp(temp->data, "<<") == 0)
        {
            break ;
        }
        find_args(unit, temp, &i);
        temp = temp->next;
    }
}

void read_the_input(char *rl, t_lexer *input)
{
    char **result;
    t_unit *unit;
    
    result = split_args(rl);
    input = add_lexers_to_list(result);
    if (!input)
        return ;
    unit = malloc(sizeof(t_unit));
    unit->data = malloc(sizeof(t_node));
    unit->data->flags_count = count_flags(input);
    add_cmds_flags_to_linked_list(input, &unit);
    unit->data->args_count = count_args(unit, input);
    add_args_to_linked_list(input, unit);
    int i;
    // int j;
    while (unit)
    {
        printf("unit->data->cmd: %s\n", unit->data->cmd);
        i = 0;
        while (i < 1)
        {
            printf("unit->data->flags[%d]: %s\n", i, unit->data->flags[i]);
            i++;
        }
        // j = 0;
        // while (j < 1)
        // {
        //     printf("unit->data->args[%d]: %s\n", j, unit->data->args[j]);
        //     j++;
        // }
        unit = unit->next;
    }
    free(result);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:43:30 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/06 19:10:05 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *retrieve_cmd_name(char *cmd_path)
{
    char *cmd_name;

    cmd_name = ft_strrchr(cmd_path, '/');
    if (cmd_name == NULL)
        return (cmd_path);
    return (cmd_name + 1);
}

int count_args(t_unit *unit, t_lexer *input)
{
    int args_count;
    t_lexer *temp;
    char *cmd_name;

    args_count = 0;
    cmd_name = retrieve_cmd_name(unit->data->cmd);
    temp = input;
    while (temp)
    {
        if (ft_strcmp(temp->data, cmd_name) != 0 && temp->data[0] != '-')
            args_count++;
        temp = temp->next;
    }
    return (args_count);
}

void find_args(t_unit *unit, t_lexer *temp, int *i)
{
    char *cmd_name;

    cmd_name = retrieve_cmd_name(unit->data->cmd);
    if (!cmd_name)
        return ;
    if (ft_strcmp(temp->data, cmd_name) != 0 && temp->data[0] != '-')
    {
        unit->data->args[*i] = ft_strdup(temp->data);
        (*i)++;
    }
}
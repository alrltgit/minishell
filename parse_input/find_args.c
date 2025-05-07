/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:43:30 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/07 15:09:17 by hceviz           ###   ########.fr       */
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

int count_args(t_node *unit, char **result)
{
    int args_count;
    char *cmd_name;
    int i;

    args_count = 0;
    cmd_name = retrieve_cmd_name(unit->cmd);
    i = 0;
    while (result[i])
    {
        if (ft_strcmp(result[i], cmd_name) != 0 && result[i][0] != '-')
            args_count++;
        i++;
    }
    return (args_count);
}

void find_args(t_node *unit, char **result, int *i, int *j)
{
    char *cmd_name;

    cmd_name = retrieve_cmd_name(unit->cmd);
    if (!cmd_name)
        return ;
    if (ft_strcmp(result[*j], cmd_name) != 0 && result[*j][0] != '-')
    {
        unit->args[*i] = ft_strdup(result[*j]);
        (*i)++;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:43:30 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/10 12:22:50 by apple            ###   ########.fr       */
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

int count_args_inside_loop(char **result, t_node *current_node, int *i)
{
    char *cmd_name;
    int args_count;
    int temp_i;

    temp_i = *i;
    args_count = 0;
    cmd_name = retrieve_cmd_name(current_node->cmd);
    current_node->args_count = 0;
    while (result[temp_i])
    {
        if (ft_strcmp(result[temp_i], "|") == 0 || ft_strcmp(result[temp_i], "<") == 0
            || ft_strcmp(result[temp_i], ">") == 0 || ft_strcmp(result[temp_i], ">>") == 0
            || ft_strcmp(result[temp_i], "<<") == 0)
            break ;
        if (ft_strcmp(result[temp_i], cmd_name) != 0 && result[temp_i][0] != '-')
            args_count++;
        temp_i++;
    }
    // printf("temp_i: %d\n", *temp_i);
    // printf("TEST2\n");
    return (args_count);
}

int count_args(char **result, t_node *current_node)
{
    char *cmd_name;
    int i = 0;
    int args_count;

    args_count = 0;
    cmd_name = retrieve_cmd_name(current_node->cmd);
    current_node->args_count = 0;
    while (result[i])
    {
        if (ft_strcmp(result[i], "|") == 0 || ft_strcmp(result[i], "<") == 0
            || ft_strcmp(result[i], ">") == 0 || ft_strcmp(result[i], ">>") == 0
            || ft_strcmp(result[i], "<<") == 0)
            break ;
        if (ft_strcmp(result[i], cmd_name) != 0 && result[i][0] != '-')
            args_count++;
        i++;
    }
    return (args_count);
};

void find_args(t_node *current_node, char **result, int *i, int *j)
{
    char *cmd_name;

    cmd_name = retrieve_cmd_name(current_node->cmd);
    // printf("current_node->cmd: %s\n", current_node->cmd);
    if (!cmd_name)
        return ;
    // printf("result[*i]: %s\n", result[*i]);
    if (ft_strcmp(result[*i], cmd_name) != 0 && result[*i][0] != '-') // wc 
    {
        // printf("cmd_name: %s\n", cmd_name);
        current_node->args[*j] = ft_strdup(result[*i]);
        // printf("current_node->args[%d]: %s\n", *j, current_node->args[*j]);
        (*j)++;
    }
}
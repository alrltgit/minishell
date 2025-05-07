/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/06 19:44:07 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **get_path()
{
    char *path;
    char **paths;

    path = getenv("PATH");
    paths = ft_split(path, ':');
    if (!paths)
        return (NULL);
    return (paths);
}

void find_command_path(char *input, t_unit *unit, int *cmd_is_found)
{
    char *temp_result;
    char **paths;
    int i;

    paths = get_path();
    if (!paths)
        return ;
    i = 0;
    while (paths[i])
    {
        temp_result = ft_strconcat(paths[i], input);
        if (access(temp_result, X_OK) == 0)
        {
            unit->data->cmd = ft_strdup(temp_result);
            *cmd_is_found = 1;
            break ;
        }
        i++;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/06 14:20:19 by alraltse         ###   ########.fr       */
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

char *find_command_path(char *input, t_unit *unit, int *cmd_is_found)
{
    char *temp_result;
    char **paths;
    char *cmd_path;
    int i;

    cmd_path = NULL;
    paths = get_path();
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        temp_result = ft_strconcat(paths[i], input);
        if (access(temp_result, X_OK) == 0)
        {
            cmd_path = ft_strdup(temp_result);
            *cmd_is_found = 1;
            break ;
        }
        i++;
    }
    return (cmd_path);
}
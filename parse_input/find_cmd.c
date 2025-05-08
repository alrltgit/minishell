/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/08 15:24:21 by hceviz           ###   ########.fr       */
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

//retrieve func has problem
void find_command_path(char *input, t_node *unit, int *cmd_is_found)
{
    char 	*temp_result;
    char 	**paths;
    int		i;

    paths = get_path();
    if (!paths)
        return ;
    i = 0;
    while (paths[i])
    {
        temp_result = ft_strconcat(paths[i], input);
        if (access(temp_result, X_OK) == 0)
        {
            unit->path = ft_strdup(temp_result);
			unit->cmd = retrieve_cmd_name(unit->path);
            *cmd_is_found = 1;
            break ;
        }
        i++;
    }
}
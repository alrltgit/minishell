/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/11 14:46:09 by hceviz           ###   ########.fr       */
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

int find_command_path(char *input, t_node *unit, int *cmd_is_found)
{
    char *temp_result;
    char **paths;
    int i;

    if (is_builtin(input))
	{
		*cmd_is_found = 1;
		unit->cmd = input;
		return (1);
	}
    paths = get_path();
    if (!paths)
        return (0);
    i = 0;
    while (paths[i])
    {
        temp_result = ft_strconcat(paths[i], input);
        if (access(temp_result, X_OK) == 0)
        {
            unit->cmd = ft_strdup(temp_result);
            *cmd_is_found = 1;
            return (2);
            break ;
        }
        i++;
    }
    return (0);
}

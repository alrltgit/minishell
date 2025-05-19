/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/19 20:11:52 by apple            ###   ########.fr       */
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
            free(temp_result);
            free_arr(paths);
            return (2);
            break ;
        }
        free(temp_result);
        i++;
    }
    free_arr(paths);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/31 16:17:13 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(void)
{
	char	*path;
	char	**paths;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

int find_command_path(char *input, t_node *unit)
{
	char	*temp_result;
	char	**paths;
	int		i;

	/* if (input[0] == '$')
		return (2); */
	if (is_builtin(input))
	{
		unit->cmd_is_found = 1;
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
            unit->cmd_is_found = 1;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/02 14:27:43 by alraltse         ###   ########.fr       */
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

void set_error_status(char *input, t_node *unit)
{
    if (ft_strchr(input, '/'))
    {
        if (access(input, F_OK) != 0)
            ft_printf("minishell: %s: No such file or directory\n", input);
        else if (access(input, X_OK) != 0)
            ft_printf("minishell: %s: Permission denied\n", input);
    }
    else
        ft_printf("minishell: %s: command not found\n", input);
    unit->cmd_status = 127;
}

int find_command_path(char *input, t_node *unit)
{
	char	*temp_result;
	char	**paths;
	int		i;

	if (is_builtin(input))
	{
		unit->cmd_is_found = 1;
		unit->cmd = input;
		return (1);
	}
    paths = get_path();
    if (!paths)
    {
        set_error_status(input, unit);
        return (0);
    }
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
        }
        free(temp_result);
        i++;
    }
    free_arr(paths);
    set_error_status(input, unit);
    return (0);
}

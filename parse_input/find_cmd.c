/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/18 17:29:56 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_error_status(char *input, t_node *unit)
{
	// printf("input %s\n", input);
	if (ft_strchr(input, '/'))
	{
		if (access(input, F_OK) != 0)
			printf("\e[0;31mminishell: %s: No such file or directory\n", input);
		else if (access(input, X_OK) != 0)
			printf("\e[0;31mminishell: %s: Permission denied\n", input);
		else if (!fake_perfect(input))
			printf("minishell: syntax error\n");
	}
	else
	{
		if (ft_strcmp(input, " ") == 0)
			printf("\e[0;31mminishell: '%s': command not found333\n", input);
		else
			printf("\e[0;31mminishell: %s: command not found333\n", input);
	}
	unit->cmd_status = 127;
	unit->shell->exit_code = 127; //new exit code logic
}

int	check_builtin_command(char *input, t_node *unit)
{
	if (is_builtin(input))
	{
		unit->cmd_is_found = 1;
		unit->cmd = input;
		unit->cmd_status = 1;
		unit->fcmd = ft_strjoin_free(unit->fcmd, input);
		return (1);
	}
	return (0);
}

void	handle_command_init(t_node *unit, char *temp_result, char **paths)
{
	unit->cmd = ft_strdup(temp_result);
	unit->fcmd = ft_strjoin_free(unit->fcmd, temp_result);
	unit->cmd_is_found = 1;
	free(temp_result);
	free_arr(paths);
	unit->cmd_status = 2;
	//unit->shell->exit_code = 2;
}

int	resolve_cmd_in_paths(char **paths, char *input, t_node *unit)
{
	char	*temp_result;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp_result = ft_strconcat(paths[i], input);
		if (access(temp_result, X_OK) == 0)
		{
			handle_command_init(unit, temp_result, paths);
			return (unit->cmd_status);
		}
		free(temp_result);
		i++;
	}
	return (0);
}

int	find_command_path(char *input, t_node *unit)
{
	char	**paths;

	if (ft_strcmp(input, "<") == 0 || is_file_name(unit, input) == 1)
	{
		unit->cmd_status = 0;
		unit->cmd = NULL;
		return (unit->cmd_status);
	}
	if (check_builtin_command(input, unit))
		return (unit->cmd_status);
	if (check_for_executable(unit, input) != 0)
		return (unit->cmd_status);
	paths = get_path();
	if (!paths)
	{
		set_error_status(input, unit);
		return (0);
	}
	if (resolve_cmd_in_paths(paths, input, unit))
		return (unit->cmd_status);
	free_arr(paths);
	set_error_status(input, unit);
	return (unit->cmd_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/30 13:34:23 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_error_status(char *input, t_node *unit)
{
	if (fake_perfect(input) == 0)
	{
		printf("minishell: %s: syntax error\n", input);
		unit->shell->exit_code = 2;
		unit->cmd_status = 127;
		return ;
	}
	else if (ft_strchr(input, '/'))
	{
		if (access(input, F_OK) != 0)
			printf("\e[0;31mminishell: %s: No such file or directory\n", input);
		else if (access(input, X_OK) != 0)
			printf("\e[0;31mminishell: %s: Permission denied\n", input);
	}
	else
	{
		ft_printf("minishell: %s: command not found\n", input);	
		printf("exit code is set to 127\n");
		unit->shell->exit_code = 127;
	}
	unit->cmd_status = 127;
}

int	check_builtin_command(char *input, t_node *unit)
{
	if (is_builtin(input))
	{
		printf("builtin cmd name %s\n", input);
		unit->cmd_is_found = 1;
		unit->cmd = ft_strdup(input);
		unit->cmd_status = 1;
		unit->fcmd = ft_strjoin_free(unit->fcmd, input);
		return (1);
	}
	return (0);
}

void	handle_command_init(t_node *unit, char *temp_result, char **paths)
{
	unit->cmd = ft_strdup(temp_result);
	printf("handle command init cmd-> %s\n", unit->cmd);
	unit->fcmd = ft_strjoin_free(unit->fcmd, temp_result);
	unit->cmd_is_found = 1;
	free(temp_result);
	free_arr(paths);
	unit->cmd_status = 2;
	unit->shell->exit_code = 0;
}

int	resolve_cmd_in_paths(char **paths, char *input, t_node *unit)
{
	char	*temp_result;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp_result = ft_strconcat(paths[i], input);
		if (access(temp_result, X_OK) == 0 && unit->cmd_is_found == 0)
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

	printf("input: %s\n", input);
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
	// printf("path func return -> %d\n", unit->cmd_status);
	return (unit->cmd_status);
}

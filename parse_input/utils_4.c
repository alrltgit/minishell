/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:13:08 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/17 19:13:40 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_for_executable(t_node *unit, char *input)
{
	
	if (ft_strchr(input, '/') != NULL)
	{
		if (access(input, F_OK) != 0)
		{
			ft_printf("minishell: %s: No such file or directory\n", input);
			unit->cmd_status = 127;
			return (unit->cmd_status);
		}
		if (access(input, X_OK) != 0)
		{
			ft_printf("minishell: %s: Permission denied\n", input);
			unit->cmd_status = 126;
			return (unit->cmd_status);
		}
		unit->cmd = ft_strdup(input);
		unit->cmd_status = 2;
		return (unit->cmd_status);
	}
	return (0);
}
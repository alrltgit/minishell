/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:51:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/30 17:21:38 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_executable_errors(t_node *unit, char *input, struct stat *sb)
{
	if (stat(input, sb) == 0 && S_ISDIR(sb->st_mode))
	{
		ft_printf("minishell: %s: Is a directory\n", input);
		unit->cmd_status = 126;
		return (unit->cmd_status);
	}
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
	return (0);
}

char	*extract_token_helper(char *token, int *count, char **result, int *i)
{
	(*i)++;
	token = ft_strdup("|");
	if (!token)
		return (NULL);
	result[(*count)++] = token;
	return (token);
}

void	init_vars_in_func(int *single_q, int *double_q)
{
	*single_q = 0;
	*double_q = 0;
}

char	*subtract_token(char *token, char *str, int start, int len)
{
	token = ft_substr(str, start, len);
	if (!token)
		return (NULL);
	return (token);
}

int	handle_pipe_and_move(t_node **current_node, char **result, int *i, int *j)
{
	(*current_node)->cmd_idx = *i + 1;
	*j = 0;
	if (handle_pipe(current_node, result, *i, (*current_node)->cmd_idx) == 1)
		return (1);
	(*i)++;
	return (0);
}

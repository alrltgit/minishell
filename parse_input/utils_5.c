/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:51:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/20 09:52:38 by apple            ###   ########.fr       */
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
	// printf("token[0]: %c\n", token[0]);
	// printf("token[len]: %c\n", token[len - 1]);
	// if ((token[0] == '\'' && token[1] == '\'')
	// 	&& token[len - 1] == '\'' && token[len - 2] == '\'')
	// {
	// 	token[len - 2] = '\0';
	// 	ft_memmove(token, token + 2, len - 2);
	// }
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:13:08 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/25 17:48:53 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	extra_token_check(char *token, char **result, int *count, int len)
{
	if (ft_strchr(token, '<') || ft_strchr(token, '>'))
		split_token_on_operator(token, result, count);
	else
		check_for_operator(token, result, count, len);
}

int	is_operator_char(char c)
{
	return (c == '<' || c == '>');
}

int	add_operator_token(const char *token, int i, char **result, int *count)
{
	if ((token[i] == '<' && token[i + 1] == '<')
		|| (token[i] == '>' && token[i + 1] == '>'))
	{
		result[(*count)++] = ft_substr(token + i, 0, 2);
		return (2);
	}
	else
	{
		result[(*count)++] = ft_substr(token + i, 0, 1);
		return (1);
	}
}

void	split_token_on_operator(char *token, char **result, int *count)
{
	int	i;
	int	op_len;

	i = 0;
	while (token[i])
	{
		if (is_operator_char(token[i]))
		{
			if (i > 0)
				result[(*count)++] = ft_substr(token, 0, i);
			op_len = add_operator_token(token, i, result, count);
			i += op_len;
			if (token[i])
				split_token_on_operator(ft_strdup(token + i), result, count);
			free(token);
			return ;
		}
		i++;
	}
	result[(*count)++] = token;
}

int	check_for_executable(t_node *unit, char *input)
{
	struct stat	sb;
	int			err;

	if (ft_strchr(input, '/') != NULL)
	{
		err = check_executable_errors(unit, input, &sb);
		printf("executable error-> %d\n", err);
		if (err)
			return (err);
		unit->cmd = ft_strdup(input);
		unit->cmd_status = 2;
		return (unit->cmd_status);
	}
	return (0);
}

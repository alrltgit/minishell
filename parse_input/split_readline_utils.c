/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_readline_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:10:09 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/20 12:56:11 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_heredoc_operator(char *token, char **result, int *count)
{
	char	*operator;
	char	*delim;

	if (ft_strncmp(token, "<<", 2) == 0 && ft_strlen(token) > 2)
	{
		operator = ft_strdup("<<");
		delim = ft_strdup(token + 2);
		free(token);
		result[(*count)++] = operator;
		result[(*count)++] = delim;
	}
	else if (ft_strcmp(token, "<<") == 0)
	{
		operator = ft_strdup("<<");
		free(token);
		result[(*count)++] = operator;
	}
}

void	handle_input_operator(char *token, char **result, int *count)
{
	char	*operator;
	char	*delim;

	if (ft_strncmp(token, "<", 1) == 0 && ft_strlen(token) > 1)
	{
		operator = ft_strdup("<");
		delim = ft_strdup(token + 1);
		free(token);
		result[(*count)++] = operator;
		result[(*count)++] = delim;
	}
	else if (ft_strcmp(token, "<") == 0)
	{
		operator = ft_strdup("<");
		free(token);
		result[(*count)++] = operator;
	}
}

void	handle_append_operator(char *token, char **result, int *count)
{
	char	*operator;
	char	*delim;

	if (ft_strncmp(token, ">>", 2) == 0 && ft_strlen(token) > 2)
	{
		operator = ft_strdup(">>");
		delim = ft_strdup(token + 2);
		free(token);
		result[(*count)++] = operator;
		result[(*count)++] = delim;
	}
	else if (ft_strcmp(token, ">>") == 0)
	{
		operator = ft_strdup(">>");
		free(token);
		result[(*count)++] = operator;
	}
}

void	handle_output_operator(char *token, char **result, int *count)
{
	char	*operator;
	char	*delim;

	if (ft_strncmp(token, ">", 1) == 0 && ft_strlen(token) > 1)
	{
		operator = ft_strdup(">");
		delim = ft_strdup(token + 1);
		free(token);
		result[(*count)++] = operator;
		result[(*count)++] = delim;
	}
	else if (ft_strcmp(token, ">") == 0)
	{
		operator = ft_strdup(">");
		free(token);
		result[(*count)++] = operator;
	}
}

void	check_for_operator(char *token, char **result, int *count, int len)
{
	(void)len;
	if (ft_strncmp(token, "<<", 2) == 0 || ft_strcmp(token, "<<") == 0)
		handle_heredoc_operator(token, result, count);
	else if (ft_strncmp(token, "<", 1) == 0 || ft_strcmp(token, "<") == 0)
		handle_input_operator(token, result, count);
	else if (ft_strncmp(token, ">>", 2) == 0 || ft_strcmp(token, ">>") == 0)
		handle_append_operator(token, result, count);
	else if (ft_strncmp(token, ">", 1) == 0 || ft_strcmp(token, ">") == 0)
		handle_output_operator(token, result, count);
	else
	{
		//trim_quotes_if_needed(token, len);
		result[(*count)++] = token;
	}
}

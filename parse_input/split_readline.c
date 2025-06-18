/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:39:40 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/18 16:01:05 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

void	trim_quotes_if_needed(char *token, int len)
{
	if ((token[0] == '\'' && token[len - 1] == '\'')
		|| (token[0] == '"' && token[len - 1] == '"'))
	{
		token[len - 1] = '\0';
		ft_memmove(token, token + 1, len - 1);
	}
}

char	*extract_token_v2(const char *str)
{
	int		i;
	int		single_q;
	int		double_q;
	char	*token;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (str[i])
	{
		handle_quotes_in_extract_token(str, &i, &single_q, &double_q);
		if ((str[i] == ' ' || str[i] == '\t') && !single_q && !double_q)
			break ;
		(i)++;
	}
	token = ft_substr(str, 0, i);
	if (!token)
		return (NULL);
	trim_quotes_if_needed(token, i);
	return (token);
}

char	*extract_token(char *str, int *i, char **result, int *count)
{
	int		start;
	int		single_q;
	int		double_q;
	char	*token;

	start = *i;
	token = NULL;
	init_vars_in_func(&single_q, &double_q);
	while (str[*i])
	{
		handle_quotes_in_extract_token(str, i, &single_q, &double_q);
		if (str[*i] == '|' && !single_q && !double_q)
		{
			if (*i == start)
				return (extract_token_helper(token, count, result, i));
			break ;
		}
		if ((str[*i] == ' ' || str[*i] == '\t') && !single_q && !double_q)
			break ;
		(*i)++;
	}
	token = subtract_token(token, str, start, *i - start);
	extra_token_check(token, result, count, *i - start);
	return (token);
}

char	**split_args(char *str)
{
	char	**result;
	char	*token;
	int		i;
	int		count;

	result = malloc(sizeof(char *) * 1024);
	if (!result)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (!str[i])
			break ;
		token = extract_token(str, &i, result, &count);
		if (!token)
			return (NULL);
	}
	result[count] = NULL;
	return (result);
}

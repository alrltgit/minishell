/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_readline_hasan.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:39:40 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/18 17:44:26 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_whitespace(const char *str, int *i)
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

/* char	*extract_token(const char *str, int *i, char **result, int *count)
{
	int		start;
	int		single_q;
	int		double_q;
	char	*token;

	start = *i;
	single_q = 0;
	double_q = 0;
	while (str[*i])
	{
		handle_quotes_in_extract_token(str, i, &single_q, &double_q);
		if (str[*i] == '|' && !single_q && !double_q)
        {
            if (*i == start)
            {
                (*i)++;
                token = ft_strdup("|");
                if (!token)
                    return (NULL);
                result[(*count)++] = token;
                return (token);
            }
            break;
        }
		if ((str[*i] == ' ' || str[*i] == '\t') && !single_q && !double_q)
			break ;
		(*i)++;
	}
	token = ft_substr(str, start, *i - start);
	if (!token)
		return (NULL);
	check_for_operator(token, result, count, *i - start);
	return (token);
} */
char	*extract_token(const char *str, int *i)
{
	int		start;
	int		single_q;
	int		double_q;
	int		len;
	char	*token;

	start = *i;
	single_q = 0;
	double_q = 0;

	if ((str[*i] == '\'' && str[*(i + 1)] == '"')
		|| (str[*i] == '"' && str[*(i + 1)] == '\''))
		return (NULL);
	while (str[*i])
	{
		if (str[*i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[*i] == '"' && !single_q)
			double_q = !double_q;
		else if ((str[*i] == ' ' || str[*i] == '\t') && !single_q && !double_q)
			break ;
		(*i)++;
	}
	len = *i - start;
	token = ft_substr(str, start, len);
	if (!token)
		return (NULL);
	//trim_outer(token);
	// trim_quotes_if_needed(token, len);
	return (token);
}

/* char	**split_args(char *str)
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
} */
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
		token = extract_token(str, &i);
		if (!token)
			return (NULL);
		result[count++] = token;
	}
	result[count] = NULL;
	return (result);
}
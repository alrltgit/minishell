/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:39:40 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/09 11:38:46 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void check_for_heredoc_operator(char *token, char **result, int *count, int len)
{
	if (ft_strncmp(token, "<<", 2) == 0 && ft_strlen(token) > 2)
	{
		char *heredoc_op = ft_strdup("<<");
		char *heredoc_delim = ft_strdup(token + 2);
		free(token);
		result[(*count)++] = heredoc_op;
		result[(*count)++] = heredoc_delim;
	}
	else
	{
		trim_quotes_if_needed(token, len);
		result[(*count)++] = token;
	}
}

static void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

void	trim_outer(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	if ('\'' == str[i] || '"' == str[i])
	{
		temp = ft_strdup(str);
		free(str);
		str = ft_strtrim(temp, &temp[ft_strlen(temp) - 1]);
		free(temp);
	}	
	//printf("After trim outer-> %s\n", str);
}

void	trim_quotes_if_needed(char *token, int len)
{
	if ((token[0] == '\'' && token[len - 1] == '\'')
		|| (token[0] == '"' && token[len - 1] == '"'))
	{
		token[len - 1] = '\0';
		ft_memmove(token, token + 1, len - 1);
	}
	// printf("After trim if needed-> %s\n", token);
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
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '"' && !single_q)
			double_q = !double_q;
		else if ((str[i] == ' ' || str[i] == '\t') && !single_q && !double_q)
			break ;
		(i)++;
	}
	token = ft_substr(str, 0, i);
	if (!token)
		return (NULL);
	trim_quotes_if_needed(token, i);
	return (token);
}

char	*extract_token(const char *str, int *i, char **result, int *count)
{
	int		start;
	int		single_q;
	int		double_q;
	int		len;
	char	*token;

	start = *i;
	single_q = 0;
	double_q = 0;
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
	check_for_heredoc_operator(token, result, count, len);
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

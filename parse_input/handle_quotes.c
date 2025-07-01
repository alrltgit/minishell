/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:50:17 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/01 16:14:15 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_vars(int *i, t_quotes *q, char **temp)
{
	*i = 0;
	q->sq = 0;
	q->dq = 0;
	*temp = NULL;
}

void	handle_single_quote(char *str, int *i, t_quotes *q, char **temp)
{
	q->sq = 1 - q->sq;
	*temp = handle_single_quotes(str, i);
}

void	handle_double_quote(char *str, int *i, t_quotes *q, char **temp)
{
	q->dq = 2 - q->dq;
	*temp = handle_double_quotes(str, i);
}

void	handle_regular_char(char **temp, char c)
{
	*temp = update_str(*temp, c);
}

char	*handle_quotesv2(char *str)
{
	int				i;
	t_quotes		q;
	char			*temp;

	if (!str)
		return (NULL);
	init_vars(&i, &q, &temp);
	while (str[i])
	{
		if (str[i] == '\'' && q.dq == 0)
		{
			handle_single_quote(str, &i, &q, &temp);
			continue ;
		}
		else if (str[i] == '"' && q.sq == 0)
		{
			handle_double_quote(str, &i, &q, &temp);
			continue ;
		}
		else
			handle_regular_char(&temp, str[i]);
		i++;
	}
	return (temp);
}

// char 	*handle_quotesv2(char *str)
// {
// 	int		i;
// 	int		sq;
// 	int		dq;
// 	char	*temp;
// 	i = 0;
// 	sq = 0;
// 	dq = 0;
// 	temp = NULL;
// 	if (!str)
// 		return ("");
// 	while (str[i])
// 	{
// 		if (str[i] && str[i] == '\'' && dq == 0)
// 		{
// 			sq = 1 - sq;
// 			i++;
// 			while (str[i] && str[i] != '\'')
// 			{
// 				temp = update_str(temp, str[i]);
// 				i++;
// 			}
// 			if (str[i] == '\'' && str[i + 1] == '\0')
// 			{
// 				temp = update_str(temp, ' ');
// 				++i;
// 			}
// 			continue;
// 		}
// 		if (str[i] && str[i] == '"' && sq == 0)
// 		{
// 			dq = 2 - dq;
// 			i++;
// 			while (str[i] && str[i] != '"')
// 			{
// 				temp = update_str(temp, str[i]);
// 				i++;
// 			}
// 			if (str[i] == '"' && str[i + 1] == '\0')
// 			{
// 				temp = update_str(temp, ' ');
// 				++i;
// 			}
// 			continue;
// 		}
// 		temp = update_str(temp, str[i]);
// 		i++;
// 	}
// 	free(str);
// 	str = ft_strdup(temp);
// 	free(temp);
// 	return (str);
// }

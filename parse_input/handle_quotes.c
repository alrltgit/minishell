/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:50:17 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/13 12:24:32 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//counts apos or double quotes according to given mode
//and checks quotes are proper or not
/* int	is_proper_quoted(char *str)
{
	int	d_q;
	int	s_q;
	int	i;

	i = -1;
	d_q = 0;
	s_q = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			++s_q;
		else if (str[i] == '"')
			++d_q;
	}
	if ((d_q % 2 == 1) || (s_q % 2 == 1))
		return (0);
	return (1);
} */

char 	*handle_quotesv2(char *str)
{
	int		i;
	int		sq;
	int		dq;
	char	*temp;

	i = 0;
	sq = 0;
	dq = 0;
	temp = NULL;
	// "'"$PATH"'"
	// printf("BEFORE HANDLING QUOTES -> %s\n", str);
	/* if (!is_proper_quoted((*str)))
		return (0); */
	if (!str)
	{
		str = update_str(str, '\'');
		str = update_str(str, '\'');
		return (str);
	}
	while (str[i])
	{
		if (str[i] && str[i] == '\'' && dq == 0)
		{
			sq = 1 - sq;
			i++; //skip opening quote
			while (str[i] && str[i] != '\'') //read until closing quote
			{
				temp = update_str(temp, str[i]);
				i++;
			}
			if (str[i] == '\'')
				++i;
			continue;
		}
		if (str[i] && str[i] == '"' && sq == 0)
		{
			dq = 2 - dq;
			i++; //skip opening quote
			while (str[i] && str[i] != '"')
			{
				temp = update_str(temp, str[i]);
				i++;
			}
			if (str[i] == '"')
				++i;
			continue;
		}
		temp = update_str(temp, str[i]);
		i++;
	}
	// printf("AFTER HANDLING QUOTES -> %s\n", temp);
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

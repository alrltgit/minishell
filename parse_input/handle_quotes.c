/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:50:17 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/21 16:23:44 by hceviz           ###   ########.fr       */
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
	/* if (!is_proper_quoted((*str)))
		return (0); */
	if (!str)
		return ("");
	while (str[i])
	{
		if (str[i] && str[i] == '\'' && dq == 0)
		{
			sq = 1 - sq;
			i++; //skip opening quote
			while (str[i] && str[i] != '\'') //read until closing quote
			{
				//while
				temp = update_str(temp, str[i]);
				i++;
			}
			if (str[i] == '\'' && str[i + 1] == '\0')
			{
				temp = update_str(temp, ' ');
				++i;
			}
			continue;
		}
		if (str[i] && str[i] == '"' && sq == 0)
		{
			dq = 2 - dq;
			i++; //skip opening quote
			while (str[i] && str[i] != '"') //while
			{
				temp = update_str(temp, str[i]);
				i++;
			}
			if (str[i] == '"' && str[i + 1] == '\0')
			{
				temp = update_str(temp, ' ');
				++i;
			}
			continue;
		}
		temp = update_str(temp, str[i]);
		i++;
	}
	free(str);
	return (temp);
	/* printf("str-> %s temp-> %s\n", str, temp);	
	str = ft_strdup(temp);
	free(temp);
	// printf("returned-> %s\n", str);
	return (str); */
}
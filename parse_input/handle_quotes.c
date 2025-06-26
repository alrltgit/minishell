/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:50:17 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/25 13:19:03 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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
	str = ft_strdup(temp);
	free(temp);
	// printf("returned-> %s\n", str);
	return (str);
}

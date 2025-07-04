/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:50:17 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/04 13:27:46 by hceviz           ###   ########.fr       */
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
	char	*old_temp;

	q->sq = 1 - q->sq;
	old_temp = *temp;
	*temp = handle_single_quotes(str, i);
	free(old_temp);
}

void	handle_double_quote(char *str, int *i, t_quotes *q, char **temp)
{
	char	*old_temp;

	q->dq = 2 - q->dq;
	old_temp = *temp;
	*temp = handle_double_quotes(str, i);
	free(old_temp);
}

char	*handle_quotesv2(char *str)
{
	int				i;
	t_quotes		q;
	char			*temp;

	temp = NULL;
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
			temp = update_str(temp, str[i]);
		i++;
	}
	return (temp);
}

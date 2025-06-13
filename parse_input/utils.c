/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/13 12:46:43 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	alloc_mem_for_flags_arr(t_node *current_node)
{
	if (current_node->flags_count > 0)
	{
		current_node->flags = malloc(sizeof(char *)
				* (current_node->flags_count + 1));
		if (!current_node->flags)
			return (1);
	}
	else
	{
		current_node->flags = malloc(sizeof(char *));
		if (!current_node->flags)
			return (1);
		current_node->flags[0] = NULL;
	}
	return (0);
}

char	*handle_single_quotes(const char *str, int *i)
{
	char	*temp;

	temp = NULL;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			continue ;
		temp = update_str(temp, str[*i]);
	}
	return (temp);
}

char	*handle_double_quotes(const char *str, int *i)
{
	char	*temp;

	temp = NULL;
	while (str[++(*i)])
	{
		if (str[*i] == '"')
			continue ;
		temp = update_str(temp, str[*i]);
	}
	return (temp);
}

void	init_vars(int *i, int *sq, int *dq, char **temp)
{
	*i = 0;
	*sq = 0;
	*dq = 0;
	*temp = NULL;
}

char	*handle_quotes(char *str)
{
	int		i;
	int		sq;
	int		dq;
	char	*temp;

	if (!str)
		return (NULL);
	init_vars(&i, &sq, &dq, &temp);
	while (str[i])
	{
		if (str[i] && str[i] == '\'' && dq == 0)
		{
			sq = 1 - sq;
			temp = handle_single_quotes(str, &i);
			continue;
		}
		else if (str[i] && str[i] == '"' && sq == 0)
		{
			dq = 2 - dq;
			temp = handle_double_quotes(str, &i);
			continue;
		}
		else
			temp = update_str(temp, str[i]);
		i++;
	}
	return (temp);
}

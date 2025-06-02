/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/06/02 15:41:31 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_flags(char **result, int j)
{
	int	flags_count;

	flags_count = 0;
	while (result[j])
	{
		if (ft_strcmp(result[j], "|") == 0)
			break ;
		if (result[j][0] == '-')
			flags_count++;
		j++;
	}
	return (flags_count);
}

void	find_flags(char *result, t_node *current_node, int *i)
{
	if (result[0] == '-')
	{
		printf("TEST_1\n");
		current_node->flags[*i] = ft_strdup2(result);
		(*i)++;
	}
}

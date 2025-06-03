/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/06/03 11:13:06 by hceviz           ###   ########.fr       */
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
		if (result[j][0] == '-' && result[j][1] != '$')
			flags_count++;
		j++;
	}
	return (flags_count);
}

void	find_flags(char *result, t_node *current_node, int *i)
{
	if (result[0] == '-' && result[1] != '$')
	{
		current_node->flags[*i] = ft_strdup2(result);
		current_node->fcmd = ft_strjoin_free(current_node->fcmd, result); //check
		(*i)++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/05/19 12:04:05 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_flags(char **result, int j)
{
    int flags_count;

    flags_count = 0;
    while (result[j])
    {
        if (is_operator(result[j]))
            break ;
        if (result[j][0] == '-')
            flags_count++;
        j++;
    }
    return (flags_count);
}

void find_flags(char *result, t_node *unit, int *i)
{
	
    if (result[0] == '-')
    {
        unit->flags[*i] = ft_strdup(result);
        (*i)++;
    }
    else
        return ;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/05/18 22:53:46 by apple            ###   ########.fr       */
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

int find_flags(char *result, t_node *unit, int *i)
{
    if (result[0] == '-')
    {
        unit->flags[(*i)] = ft_strdup2(result);
        (*i)++;
        return (0);
    }
    return (1);
}


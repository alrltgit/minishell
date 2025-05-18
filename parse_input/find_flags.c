/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/05/18 17:12:44 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_flags(char **result)
{
    int flags_count;
    int i;

    flags_count = 0;
    i = 0;
    while (result[i])
    {
        if (is_operator(result[i]))
            break ;
        if (result[i][0] == '-')
            flags_count++;
        i++;
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


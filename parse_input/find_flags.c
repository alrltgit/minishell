/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/05/10 16:01:39 by alraltse         ###   ########.fr       */
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
        if (ft_strcmp(result[i], "|") == 0 || ft_strcmp(result[i], "<") == 0
            || ft_strcmp(result[i], ">") == 0 || ft_strcmp(result[i], ">>") == 0
            || ft_strcmp(result[i], "<<") == 0)
            break ;
        if (result[i][0] == '-')
            flags_count++;
        i++;
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
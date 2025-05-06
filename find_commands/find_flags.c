/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/05/06 14:09:12 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_flags(t_lexer *input)
{
    int flags_count;
    t_lexer *temp;

    flags_count = 0;
    temp = input;
    while (temp)
    {
        if (ft_strcmp(temp->data, "|") == 0 || ft_strcmp(temp->data, "<") == 0
            || ft_strcmp(temp->data, ">") == 0 || ft_strcmp(temp->data, ">>") == 0
            || ft_strcmp(temp->data, "<<") == 0)
            break ;
        if (temp->data[0] == '-')
            flags_count++;
        temp = temp->next;
    }
    return (flags_count);
}

void find_flags(t_lexer *temp, t_unit *unit, int *i)
{
    if (temp->data[0] == '-')
    {
        // printf("temp->data: %s\n", temp->data);
        unit->data->flags[*i] = ft_strdup(temp->data);
        // printf("unit->data->flags[0]: %s\n", unit->data->flags[0]);
        (*i)++;
    }
}
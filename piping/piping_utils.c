/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:52:20 by apple             #+#    #+#             */
/*   Updated: 2025/05/17 16:40:54 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int find_list_len(t_node *node)
{
    t_node *temp;
    int count;

    temp = node;
    count = 0;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    return (count);
}



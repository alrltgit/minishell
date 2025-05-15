/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:47:07 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/15 17:10:12 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_node_arr(char **arr, int arr_length)
{
    int i;

    i = 0;
    while (i < arr_length)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_linked_list(t_node *node)
{
    t_node *temp;

    while (node)
    {
        temp = node->next;
        free(node);
        node = temp;  
    }
}

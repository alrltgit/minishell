/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_unit_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:55 by apple             #+#    #+#             */
/*   Updated: 2025/05/07 14:23:21 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_unit *create_unit()
{
    t_unit *node;

    node = malloc(sizeof(t_unit));
    if (!node)
        return (NULL);
    node->data = malloc(sizeof(t_node));
    if (!node->data)
    {
        free(node);
        return (NULL);
    }
    node->data->cmd = NULL;
    node->data->flags = NULL;
    node->data->args = NULL;
    node->next = NULL;
	node->shell = NULL;
    return (node);
}

t_unit *add_unit_to_end(t_unit **head)
{
    t_unit *temp;
    t_unit *new_node;

    new_node = create_unit();
    if (!new_node)
        return (NULL);
    if (!*head)
    {
        *head = new_node;
        return (new_node);
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
    return (new_node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_unit_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:55 by apple             #+#    #+#             */
/*   Updated: 2025/05/22 14:37:38 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node *create_unit()
{
    t_node *node;

    node = malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    node->cmd = NULL;
    node->flags = NULL;
    node->args = NULL;
    node->next = NULL;
	node->shell = NULL;
	node->cmd_type = 0;
	node->is_pipe = 0;
	node->stdin_redirect = 0;
    return (node);
}

t_node *add_unit_to_end(t_node **head)
{
    t_node *temp;
    t_node *new_node;

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

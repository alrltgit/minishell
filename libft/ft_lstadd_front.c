/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:11:53 by apple             #+#    #+#             */
/*   Updated: 2025/02/21 11:26:59 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main()
// {
//     t_list *root = malloc(sizeof(t_list));
//     t_list *node_1 = malloc(sizeof(t_list));
//     t_list *node_2 = malloc(sizeof(t_list));
//     root->content = "hello2\n";
//     root->next = node_1;
//     node_1->content = "hello3\n";
//     node_1->next = NULL;
//     node_2->content = "hello1\n";
//     ft_lstadd_front(&root, node_2);
//     while (root != NULL)
//     {
//         printf("%s", (char *)root->content);
//         root = root->next;
//     }
//     return (0);
// }

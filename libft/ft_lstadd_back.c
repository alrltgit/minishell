/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:19:47 by alraltse          #+#    #+#             */
/*   Updated: 2025/02/18 16:47:53 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}

// int main()
// {
//     t_list *root = malloc(sizeof(t_list));
//     t_list *node_1 = malloc(sizeof(t_list));
//     t_list *node_2 = malloc(sizeof(t_list));
//     t_list *node_3 = malloc(sizeof(t_list));
//     root->content = "hello\n";
//     root->next = node_1;
//     node_1->content = "hello\n";
//     node_1->next = NULL;
//     node_2->content = "hello\n";
//     node_2->next = NULL;
//     node_3->content = "hello\n";
//     node_3->next = NULL;
//     ft_lstadd_back(&root, node_2);
//     ft_lstadd_back(&root, node_3);
//     while(root != NULL)
//     {
//         printf("%s", (char *)root->content);
//         root = root->next;
//     }
//     return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:33:32 by alraltse          #+#    #+#             */
/*   Updated: 2025/03/01 15:38:48 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *lst_content)
{
	if (lst_content)
		lst_content = NULL;
	free(lst_content);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;

	while (*lst)
	{
		curr = (*lst)->next;
		del(curr->content);
		free(*lst);
		*lst = curr;
	}
}

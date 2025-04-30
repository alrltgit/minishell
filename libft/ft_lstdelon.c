/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:52:18 by alraltse          #+#    #+#             */
/*   Updated: 2025/03/01 15:34:59 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *lst_content)
{
	if (lst_content)
		lst_content = NULL;
	free(lst_content);
}

void	ft_lstdelon(t_list *lst, void (*del)(void *))
{
	del(lst->content);
}

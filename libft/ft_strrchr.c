/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:47:20 by alraltse          #+#    #+#             */
/*   Updated: 2024/12/19 14:13:03 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_dup;
	int		size;

	s_dup = (char *)s;
	size = 0;
	while (s_dup[size])
		size++;
	while (size >= 0)
	{
		if (s_dup[size] == (char)c)
			return (&s_dup[size]);
		size--;
	}
	return (NULL);
}

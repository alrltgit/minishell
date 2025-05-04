/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:47:31 by alraltse          #+#    #+#             */
/*   Updated: 2024/12/19 13:15:18 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s_1;
	unsigned char	*s_2;

	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s_1 != *s_2)
		{
			if (*s_1 > *s_2)
				return (*s_1 - *s_2);
			else if (*s_1 < *s_2)
				return (*s_1 - *s_2);
		}
		n--;
		s_1++;
		s_2++;
	}
	return (0);
}

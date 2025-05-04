/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:45:08 by alraltse          #+#    #+#             */
/*   Updated: 2025/03/01 15:36:42 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_copy;
	unsigned char	*s2_copy;

	s1_copy = (unsigned char *)s1;
	s2_copy = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (s1_copy[i] && s2_copy[i] && i < n)
	{
		if (s1_copy[i] < s2_copy[i])
			return (s1_copy[i] - s2_copy[i]);
		else if (s1_copy[i] > s2_copy[i])
			return (s1_copy[i] - s2_copy[i]);
		i++;
	}
	if (i < n)
		return (s1_copy[i] - s2_copy[i]);
	return (0);
}

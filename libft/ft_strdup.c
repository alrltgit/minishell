/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:21:49 by apple             #+#    #+#             */
/*   Updated: 2025/06/23 21:07:34 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	char	*p;
	int		i;

	// ft_printf("s1: %s\n", s1);
	i = 0;
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (ptr == NULL)
		return (NULL);
	p = ptr;
	i = 0;
	while (s1[i])
	{
		*p = s1[i];
		p++;
		i++;
	}
	*p = '\0';
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:15:51 by apple             #+#    #+#             */
/*   Updated: 2025/06/01 16:27:09 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	length;
	size_t	end;

	length = ft_strlen(s);
	end = 0;
	if (start < length)
		end = length - start;
	if (len < end)
		end = len;
	ptr = malloc(end + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < end)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

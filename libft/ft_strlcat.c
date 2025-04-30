/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:10:53 by apple             #+#    #+#             */
/*   Updated: 2024/12/21 14:51:38 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dst, const char *src, size_t size_dst, size_t val)
{
	size_t	i;

	i = 0;
	while (src[i] && i < val - 1)
	{
		dst[size_dst] = src[i];
		i++;
		size_dst++;
	}
	dst[size_dst] = '\0';
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size_dst;
	size_t	size_dst_val;
	size_t	size_src;
	size_t	val;

	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	size_dst_val = size_dst;
	if (size_dst_val >= dstsize)
		return (dstsize + size_src);
	val = dstsize - size_dst;
	ft_strcpy(dst, src, size_dst, val);
	return (size_dst_val + size_src);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:14:38 by apple             #+#    #+#             */
/*   Updated: 2025/05/12 14:57:53 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcon(char const *s1, char const *s2, char *ptr)
{
	int		i;
	int		j;
	char	*p;

	p = ptr;
	i = 0;
	while (s1[i])
	{
		*p = s1[i];
		p++;
		i++;
	}
	j = 0;
	while (s2[j])
	{
		*p = s2[j];
		p++;
		j++;
	}
	*p = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ptr = malloc(i + j + 1);
	if (ptr == NULL)
		return (NULL);
	return (ft_strcon(s1, s2, ptr));
}

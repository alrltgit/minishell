/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:07:06 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/13 13:04:50 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	q;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = ' ';
	q = 0;
	while (s2[q])
		res[i++] = s2[q++];
	res[i] = '\0';
	free(s1);
	return (res);
}

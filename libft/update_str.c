/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:11:02 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/20 16:30:50 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*update_str(char *old, char c)
{
	int		i;
	char	*res;

	if (!c)
		return (old);
	if (!old)
		old = ft_strdup("");
	res = malloc(ft_strlen(old) + 2);
	i = -1;
	while (old[++i])
		res[i] = old[i];
	res[i] = c;
	res[i + 1] = '\0';
	free(old);
	return (res);
}

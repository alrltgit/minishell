/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_strings_with_spaces.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:07:32 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/22 18:31:24 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_strings_with_spaces(int size, int count, char **arr)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	str = malloc(sizeof(char) * (size + count));
	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (i < count)
	{
		j = 0;
		while (arr[i][j])
			str[k++] = arr[i][j++];
		if (i < count - 1)
			str[k++] = ' ';
		i++;
	}
	str[k] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:02:14 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/22 18:31:53 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_arr_size(char **arr, int arr_count)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < arr_count)
	{
		j = 0;
		while (arr[i][j])
		{
			count++;
			j++;
		}
		i++;
	}
	return (count);
}

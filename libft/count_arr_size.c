/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:02:14 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/13 14:04:09 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int count_arr_size(char **arr, int arr_count)
{
	int i;
	int j;
	int count;

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
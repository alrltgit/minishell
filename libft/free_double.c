/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:38:49 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/26 16:22:28 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//parameter is void to handle all types
void	free_double(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

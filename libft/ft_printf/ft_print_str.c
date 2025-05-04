/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:33:55 by apple             #+#    #+#             */
/*   Updated: 2025/01/31 15:49:27 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *s)
{
	int	i;
	int	str_size;

	str_size = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		str_size = ft_strlen_pf("(null)");
		return (str_size);
	}
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	str_size = i;
	return (str_size);
}

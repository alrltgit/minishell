/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:05:51 by apple             #+#    #+#             */
/*   Updated: 2025/01/31 15:50:29 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_dec(int n)
{
	char	*nb;
	int		str_size;

	str_size = 0;
	nb = ft_itoa(n);
	ft_print_str(nb);
	str_size = ft_strlen_pf(nb);
	free(nb);
	return (str_size);
}

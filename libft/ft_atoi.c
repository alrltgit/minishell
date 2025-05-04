/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:47:52 by alraltse          #+#    #+#             */
/*   Updated: 2025/03/18 21:29:43 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_for_isspace(char *str, int *i, int *sign)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
}

static int	check_int_limits(long new_nb, int *error_flag)
{
	if (new_nb > INT_MAX || new_nb < INT_MIN)
	{
		*error_flag = 1;
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *nptr, int *error_flag)
{
	char	*str;
	int		i;
	long	new_nb;
	int		sign;

	str = (char *)nptr;
	i = 0;
	sign = 1;
	new_nb = 0;
	check_for_isspace(str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (new_nb > (LONG_MAX - (str[i] - '0')) / 10)
		{
			*error_flag = 1;
			return (0);
		}
		new_nb = new_nb * 10 + (str[i] - '0');
		i++;
	}
	new_nb *= sign;
	if (!check_int_limits(new_nb, error_flag))
		return (0);
	return ((int)new_nb);
}

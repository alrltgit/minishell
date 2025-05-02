/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:11:08 by apple             #+#    #+#             */
/*   Updated: 2025/02/01 16:44:33 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include "../libft.h"

int		ft_printf(const char *fixed_arg, ...);
int		ft_print_dec(int n);
int		ft_print_hex_lower(unsigned int val);
int		ft_print_hex_upper(unsigned int val);
int		ft_print_pointer(void *val);
int		ft_print_str(char *s);
int		ft_print_undec(unsigned int num);
int		ft_strlen_pf(char *s);

#endif

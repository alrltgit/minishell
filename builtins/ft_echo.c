/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:33 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/05 12:57:39 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	if echo has -n flag, at least there must be
	one space between echo and -n. Otherwise, it cannot
	execute.
	->echo "            abcdef"
	->echo             abcdef
	These 2 are not same
	First one will be printed with spaces
	Second one will be printed without spaces

	SO
	if the argument is in quotes, handle the quotes and
	take everything inside the quotes(space,tab etc)
	if it is not in quotes, trim spaces between echo and first
	arg
*/
void	ft_echo(t_cmd *command)
{
	
}
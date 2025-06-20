/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:33 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/20 16:50:56 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	if there is expansion variable somewhere
	in the command->fcmd and if it is not exist expansion,
	and if there is command, exrecute the command

	for ex: $abcdef echo abc -> abc
	for ex: echo abc $abcdef -> abc
	for ex: echo $abcdef abc -> abc
	so it replaces nothing to $abcdef cuz
	it is not exist.
	
	try with echo -$abcdefd

*/
void	ft_echo(t_node *command)
{
	
	(void)command;
	
	int	i;
	int	w_n;
	int	len;

	w_n = 0;
	i = -1;
	print_node(command);
	len = ft_strlen(command->fcmd);	
	i = 4;
	if (command->fcmd[5] == '-' && command->fcmd[6] == 'n' && (command->fcmd[7] == '\0'
			|| command->fcmd[7] == ' '))
	{
		w_n = 1;
		i = 7;
	}
	while (++i < len)
		write(1, &command->fcmd[i], 1);
	if (!w_n)
		printf("\n");
	command->shell->exit_code = 0;
}

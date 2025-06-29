/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:33 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/29 11:56:51 by hceviz           ###   ########.fr       */
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

void	handle_n_flag(t_node *command, int *i, int *w_n)
{

	//echo -n fdgdfgd
	if (command->fcmd[5] == '-' && command->fcmd[6] == 'n')
	{
		if (command->fcmd[7] && command->fcmd[7] != ' ' && command->fcmd[7] != '\0')
			return ;
		// if (command->fcmd[7] == ' ' ||)
		else
		{
			*i = 7;
			while (command->fcmd[*i + 1] == '-'
				&& command->fcmd[*i + 2] == 'n' 
				&& (command->fcmd[*i + 3] == ' '
			|| command->fcmd[*i + 3] == '\0'))
			{
				*i += 3;
				
			}
			*w_n = 1;
		}
	}
}

void	ft_echo(t_node *command)
{
	
	//(void)command;
	
	int	i;
	int	w_n;
	int	len;

	w_n = 0;
	i = -1;
	len = ft_strlen(command->fcmd);	
	i = 4;
	printf("fcmd before handle n flag -> %s\n", command->fcmd);
	if (command->fcmd[4] && command->fcmd[5] && command->fcmd[6]
		&& command->fcmd[4] == ' ' && command->fcmd[5] )
	handle_n_flag(command, &i, &w_n);
	printf("fcmd after handle n flag -> %s\n", command->fcmd);
	while (++i < len)
		write(1, &command->fcmd[i], 1);
	if (!w_n)
		printf("\n");
}

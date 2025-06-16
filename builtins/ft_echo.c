/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:33 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/16 17:18:00 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_input(char **input_split, int count)
{
	int	i;
	int	w_n;

	w_n = 0;
	i = 0;
	if (ft_strcmp(input_split[1], "-n") == 0)
	{
		w_n = 1;
		++i;
	}
	while (input_split[++i])
	{
		if (i + 1 != count)
			printf("%s ", input_split[i]);
		else
		{
			printf("%s", input_split[i]);
			if (!w_n)
				printf("\n");
		}
	}
}


/*
	if there is expansion variable somewhere
	in the input and if it is not exist expansion,
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
	int		count;
	char	**input_split;

	(void)command;
	// printf("fcmd-> %s\n", command->fcmd);
	input_split = split_args(command->fcmd);
	count = 0;
	if (ft_strcmp(input_split[0], "echo") == 0 && !input_split[1])
	{
		printf("\n");
		return ;
	}
	while (input_split[count])
		count++;
	process_input(input_split, count);
	free_double((void **)input_split);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:33 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/19 16:53:04 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_input(char **input_split, int count)
{
	int	i;

	if (ft_strcmp(input_split[1], "-n") == 0)
	{
		i = 1;
		while (input_split[++i])
		{
			if (i + 1 != count)
				printf("%s ", input_split[i]);
			else
				printf("%s", input_split[i]);
		}
	}
	else
	{
		i = 0;
		while (input_split[++i])
		{
			if (i + 1 != count)
				printf("%s ", input_split[i]);
			else
				printf("%s", input_split[i]);
		}
		printf("\n");
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
	input_split = split_args(rl_line_buffer);
	count = -1;
	
	if (ft_strcmp(input_split[0], "echo") == 0 && !input_split[1])
	{
		printf("\n");
		return;
	}
	while (input_split[++count])
		;
	process_input(input_split, count);
	free_double((void **)input_split);
}

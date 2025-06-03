/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:33 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/03 12:24:03 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_input(char **input_split, int count)
{
	int	i;

	if (ft_strcmp(input_split[1], "-n") == 0)
	{
		i = 1;
		while (input_split[++i] && ft_strcmp(input_split[++i], "|") == 0)
		{
			if (i + 1 != count && ft_strcmp(input_split[i + 1], "|") != 0)
				printf("%s ", input_split[i]);
			else
				printf("%s", input_split[i]);
		}
	}
	else
	{
		i = 1;
		while (input_split[i] && ft_strcmp(input_split[i], "|") != 0)
		{
			// printf("TEST\n");
			if (i + 1 != count && ft_strcmp(input_split[i + 1], "|") != 0)
				printf("%s ", input_split[i]);
			else
				printf("%s", input_split[i]);
			i++;
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
	int		len;
	char	*temp;

	(void)command;
	input_split = split_args(command->fcmd);
	
	// int i = 0;
	// while (input_split[i++])
	// {
	// 	printf("input_split[i]: %s\n", input_split[i]);	
	// }

	count = -1;
	len = -1;
	
	if (ft_strcmp(input_split[0], "echo") == 0 && !input_split[1])
	{
		printf("\n");
		return ;
	}
	while (input_split[++len])
		;
	while (++count < len)
	{
		temp = ft_strdup(input_split[count]);
		free(input_split[count]);
		input_split[count] = ft_strdup(handle_quotes(perfect(command, &temp)));
		// printf("input_split[count]: %s\n", input_split[count]);	
		//trim_outer(input_split[count]);
	}
	while (input_split[++count])
		;
	process_input(input_split, count);
	free_double((void **)input_split);
}

/* void	ft_echo(t_node *command)
{
	
} */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:17:18 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/03 16:49:12 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
readline() - takes a string as an argument and returns a read string.
char *rl is declared inside a shell_loop function because it must be freed when the loop ends. 
add_history() inside create_prompt function allows saving inputs to the history (use arrow keys to check)
*/

void read_the_input(char *rl)
{
    printf("%s\n", rl);
}

int create_prompt(char *rl)
{
    rl = readline(PS1);
	if (rl && *rl)
		add_history(rl);
	if (rl == NULL)
	{
		printf("No prompt created.\n");
		return (1);
	}
    read_the_input(rl);
    return (0);
}
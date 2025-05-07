/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:17:18 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/07 13:43:07 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int create_prompt(char *rl)
{
    rl = readline(PS1);
    read_the_input(rl);
	if (rl && *rl)
		add_history(rl);
	if (rl == NULL)
	{
		printf("No prompt created.\n");
		return (1);
	}
    return (0);
}
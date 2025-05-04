/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:17:18 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/04 13:35:03 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int create_prompt(char *rl, t_lexer *lexers)
{
    rl = readline(PS1);
    read_the_input(rl, lexers);
	if (rl && *rl)
		add_history(rl);
	if (rl == NULL)
	{
		printf("No prompt created.\n");
		return (1);
	}
    return (0);
}
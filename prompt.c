/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:17:18 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/19 20:08:02 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int create_prompt(char *rl, t_shell *shell)
{
    rl = readline(PS1);
    read_the_input(rl, shell);
	if (rl && *rl)
		add_history(rl);
	if (rl == NULL)
	{
		printf("No prompt created.\n");
		return (1);
	}
    return (0);
}

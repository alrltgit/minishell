/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:01:55 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/07 21:28:51 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
	In interactive mode, bash will response
	to signals.
	In non-interactive mode, it will not response.
*/

//WHAT CAN I DO FOR CTRL-D
//CTRL-C SENDS SIGINT SIGNAL

void	activate_ctrlc(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	deactivate_ctrlc(int sig)
{
	(void)sig;
	//printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
}
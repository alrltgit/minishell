/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:01:55 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/01 16:39:29 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./includes/minishell.h"

void	activate_ctrlc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	deactivate_ctrlc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:16:52 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/21 14:32:23 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_node *command)
{
	rl_clear_history();
	//iterate_free_nodes(command);
	//print_node(command);
	free_double((void **)command->shell->env);
	exit(0);
}

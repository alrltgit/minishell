/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:47:07 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/16 10:46:41 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	iterate_free_nodes(t_node *head)
{
	t_node	*temp;
	t_node	*next;

	temp = head;
	while (temp)
	{
		next = temp->next;
		free(temp->cmd);
		free_double((void **)temp->flags);
		free_double((void **)temp->args);
		free(temp);
		temp = next;
	}
}

void	free_exit(t_shell *shell)
{
	free_double((void **)shell->env);
	if (shell->cmds)
		iterate_free_nodes(shell->cmds);
	return ;
}

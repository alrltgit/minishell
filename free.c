/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:47:07 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/20 17:00:56 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	
	while (arr && arr[i])
	{
		printf("arr debug %d -> %s\n", i, arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
}

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

void	free_double_n(void **arr, int n)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (++i < n)
		free(arr[i]);
	free(arr);
}

void	free_exit(t_shell *shell)
{
	if (shell->cmds)
		iterate_free_nodes(shell->cmds);
	free_double((void **)shell->env);
	return ;
}

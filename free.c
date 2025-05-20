/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:47:07 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/20 14:34:02 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
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

void free_node_arr(char **arr, int arr_length)
{
    int i;

    i = 0;
    while (i < arr_length)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_linked_list(t_node *node)
{
    t_node *temp;

    while (node)
    {
        temp = node->next;
        free(node);
        node = temp;  
    }
}

void	free_exit(t_shell *shell)
{
	if (shell->cmds)
		iterate_free_nodes(shell->cmds);
	free_double((void **)shell->env);
	return ;
}

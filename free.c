/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:47:07 by alraltse          #+#    #+#             */
/*   Updated: 2025/07/02 12:37:34 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_flags_args(char **arr, int len)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < len)
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

void	free_linked_list(t_node *unit)
{
	free_node_list(unit);
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->type)
			free(redir->type);
		if (redir->file_name)
			free(redir->file_name);
		free(redir);
		redir = tmp;
	}
}

void	free_node_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->cmd)
			free(head->cmd);
		if (head->fcmd)
			free(head->fcmd);
		if (head->flags)
			free_flags_args(head->flags, head->flags_count);
		if (head->args)
			free_flags_args(head->args, head->args_count);
		if (head->redir_files)
			free_redir_list(head->redir_files);
		free(head);
		head = tmp;
	}
}

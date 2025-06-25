/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_unit_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:55 by apple             #+#    #+#             */
/*   Updated: 2025/06/25 13:24:25 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_t_redir_type(t_redir *new_node)
{
	new_node->type->stdin_redir = 0;
	new_node->type->stdout_redir = 0;
	new_node->type->append_redir = 0;
	new_node->type->heredoc_redir = 0;
	new_node->type->has_out_redir = 0;
}

void	add_node(t_redir **head, t_redir *new_node)
{
	t_redir	*temp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_redir	*add_new_file(t_redir **head, char *file_name)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (NULL);
	new_node->file_name = ft_strdup(file_name);
	if (!new_node->file_name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = malloc(sizeof(t_redir_type));
	if (!new_node->type)
	{
		free(new_node);
		return (NULL);
	}
	init_t_redir_type(new_node);
	new_node->next = NULL;
	add_node(head, new_node);
	return (new_node);
}

t_node	*create_unit(t_shell *shell)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->flags = NULL;
	node->fcmd = NULL;
	node->args = NULL;
	node->next = NULL;
	node->shell = shell;
	node->shell->exit_code = 0;
	node->redir_files = NULL;
	node->cmd_status = 0;
	node->cmd_type = 0;
	node->is_pipe = 0;
	node->cmd_is_found = 0;
	node->cmd_idx = 0;
	// node->quote_control = 0;
	return (node);
}

t_node	*add_unit_to_end(t_node **head)
{
	t_node	*temp;
	t_node	*new_node;

	new_node = create_unit((*head)->shell);
	if (!new_node)
		return (NULL);
	if (!*head)
	{
		*head = new_node;
		return (new_node);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (new_node);
}

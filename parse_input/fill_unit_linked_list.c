/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_unit_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:10:55 by apple             #+#    #+#             */
/*   Updated: 2025/06/03 16:10:38 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int init_t_redir_vars(t_node *current_node)
{
    if (!current_node->redir_files)
    {
        current_node->redir_files = malloc(sizeof(t_redir));
        if (!current_node->redir_files)
            return (1);
        current_node->redir_files->type = NULL;
        current_node->redir_files->file_name = NULL;
        current_node->redir_files->next = NULL;
    }
    if (!current_node->redir_files->type)
    {
        current_node->redir_files->type = malloc(sizeof(t_redir_type));
        if (!current_node->redir_files->type)
            return (1);
        current_node->redir_files->type->stdin_redir = 0;
        current_node->redir_files->type->stdout_redir = 0;
    }
    return (0);
}

t_redir *add_new_file(t_redir **head, char *file_name)
{
    t_redir *new_node;
    t_redir *temp;

    new_node = malloc(sizeof(t_redir));
    if (!new_node)
        return (NULL);
    new_node->type = NULL;
    new_node->file_name = ft_strdup(file_name);
    new_node->next = NULL;
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

t_node	*create_unit(void)
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
	node->shell = NULL;
	node->redir_files = NULL;
	node->cmd_status = 0;
	node->cmd_type = 0;
    node->is_pipe = 0;
    node->cmd_is_found = 0;
    return (node);
}

t_node	*add_unit_to_end(t_node **head)
{
	t_node	*temp;
	t_node	*new_node;

	new_node = create_unit();
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

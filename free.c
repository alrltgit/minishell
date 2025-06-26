/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:47:07 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/26 15:08:10 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_flags_args(char **arr, int len)
{
	int	i;

	i = 0;
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

/* free_linked_list */

void free_linked_list(t_node *unit)
{
	// free_shell(unit->shell);
	free_redir_list(unit->redir_files);
	free_node_list(unit);
}

void	free_redir_list(t_redir *redir)
{
    t_redir *tmp;
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
    t_node *tmp;
    while (head)
    {
        tmp = head->next;
        if (head->cmd)
            free(head->cmd); // cause "invalid free[]" error in pwd case
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

void	free_shell(t_shell *shell)
{
    if (shell->env)
        free_arr(shell->env);
    if (shell->cmds)
        free_node_list(shell->cmds);
    free(shell);
}

/* free_linked_list */

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

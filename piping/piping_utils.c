/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 22:22:56 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/18 16:48:10 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_pipe(t_node **current_node, char **result, int *i, int *j)
{
	int	j_temp;

	if (ft_strcmp(result[*j], "|") == 0)
	{
		(*current_node)->is_pipe = 1;
		*current_node = add_unit_to_end(current_node);
		if (!*current_node)
			return (1);
		j_temp = *j + 1;
		if (!result[j_temp])
			return (1);
		(*current_node)->flags_count = count_flags(result, j_temp);
		if (alloc_mem_for_flags_arr(*current_node) == 1)
			return (1);
		*i = 0;
		(*current_node)->cmd_is_found = 0;
		(*j)++;
	}
	return (0);
}

void	handle_child(t_node *temp, int *pipe_fd, int prev_fd)
{
	t_redir	*redir;
	t_redir	*r;
	int		has_out_redir;

	redir = temp->redir_files;
	r = redir;
	has_out_redir = handle_redir_heredoc_append(redir);
	if (has_out_redir == -1)
		exit (1);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (!has_out_redir && temp->next != NULL)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	execute_depending_on_type(t_node *temp, char **argv, t_node *node)
{
	if (temp->cmd_type == B_IN)
	{
		execute_builtin(temp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(temp->cmd, argv, node->shell->env);
		free_arr(argv);
		exit(EXIT_FAILURE);
	}
}

void	handle_parent(t_node *temp, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (temp->next)
	{
		close(pipe_fd[1]);
		prev_fd = pipe_fd[0];
	}
	else
		close(pipe_fd[0]);
}

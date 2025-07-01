/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:38:42 by apple             #+#    #+#             */
/*   Updated: 2025/07/01 16:15:13 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_pipe_fd(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (1);
	}
	return (0);
}

pid_t	create_fork(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		node->shell->exit_code = 1;
		perror("fork failed");
	}
	return (pid);
}

int	handle_pipe_and_fork(t_node *node, int pipe_fd[2], pid_t *pid)
{
	if (create_pipe_fd(pipe_fd))
	{
		node->shell->exit_code = 1;
		return (1);
	}
	*pid = create_fork(node);
	return (0);
}

int	handle_iteration(t_node **temp, int pipe_fd[2], int *prev_fd, char **result)
{
	pid_t	pid;

	if (handle_pipe_and_fork(*temp, pipe_fd, &pid))
		return (1);
	if (pid == 0)
	{
		manage_child_process(*temp, pipe_fd, *prev_fd, result);
		return (1);
	}
	else if (pid > 0)
	{
		manage_parent_process(*temp, pipe_fd, prev_fd);
		*temp = (*temp)->next;
	}
	else
		return (1);
	return (0);
}

void	create_pipe(t_node *node, char **result)
{
	t_node	*temp;
	int		prev_fd;
	int		pipe_fd[2];

	temp = node;
	prev_fd = -1;
	while (temp)
	{
		if (handle_iteration(&temp, pipe_fd, &prev_fd, result))
			return ;
	}
	temp = node;
	exit_code(temp);
	unlink("fd_temp");
}

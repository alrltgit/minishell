/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:38:42 by apple             #+#    #+#             */
/*   Updated: 2025/06/14 14:27:15 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	manage_child_process(t_node *temp, int pipe_fd[2],
	int prev_fd, t_node *node)
{
	char	**argv;

	argv = build_argv(temp);
	handle_child(temp, pipe_fd, prev_fd);
	execute_depending_on_type(temp, argv, node);
	free_arr(argv);
}

void	manage_parent_process(t_node *temp, int pipe_fd[2], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (temp->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		close(pipe_fd[0]);
}

int	create_pipe_fd(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (1);
	}
	return (0);
}

//added t_node as parameter to set shell err code in case of err
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

void	create_pipe(t_node *node)
{
	t_node	*temp;
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	pid;

	temp = node;
	prev_fd = -1;
	while (temp)
	{
		//addded errcode line for exit status
		if (create_pipe_fd(pipe_fd))
		{
			node->shell->exit_code = 1;
			return ;
		}
		pid = create_fork(node);
		if (pid == 0)
			manage_child_process(temp, pipe_fd, prev_fd, node);
		else
		{
			manage_parent_process(temp, pipe_fd, &prev_fd);
			temp = temp->next;
		}
	}
	while (wait(NULL) > 0)
		;
	unlink("fd_temp");
}

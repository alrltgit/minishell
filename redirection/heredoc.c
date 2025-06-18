/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:10:40 by apple             #+#    #+#             */
/*   Updated: 2025/06/18 16:51:47 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_child_heredoc(char *delimiter, int fd_temp)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd_temp, line, ft_strlen(line));
		write(fd_temp, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_temp);
	exit(0);
}

int	handle_parent_heredoc(pid_t pid, int fd_temp)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	close(fd_temp);
	if (WIFSIGNALED(status))
		return (1);
	return (0);
}

int	heredoc(char *delimiter)
{
	int		fd_temp;
	pid_t	pid;

	fd_temp = open("fd_temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_temp < 0)
	{
		printf("fd_temp didn't open\n");
		return (1);
	}
	pid = fork();
	if (pid == 0)
		handle_child_heredoc(delimiter, fd_temp);
	else if (pid > 0)
	{
		if (handle_parent_heredoc(pid, fd_temp) == 1)
			return (1);
	}
	else
	{
		perror("fork failed");
		return (1);
	}
	return (0);
}

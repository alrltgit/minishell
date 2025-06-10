/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:08:27 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/09 16:35:27 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_stdin_redirection(t_redir *redir)
{
	if (redirect_to_stdin(redir) == 1)
		return (1);
	return (0);
}

int	handle_stdout_redirection(t_redir *redir)
{
	if (redirect_to_stdout(redir) == 1)
		return (1);
	return (0);
}

int	handle_heredoc_redirection(t_redir *redir)
{
	int	fd;

	if (heredoc(redir->file_name) == 1)
		return (1);
	fd = open("fd_temp", O_RDONLY);
	if (fd < 0)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_append_redirection(t_redir *redir)
{
	if (append(redir) == 1)
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:42:27 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/25 13:27:49 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_child_process(t_node *node, char **argv)
{
	t_redir	*redir;

	redir = node->redir_files;
	while (redir)
	{
		handle_redir_heredoc_append(redir);
		redir = redir->next;
	}
	if (node->cmd == NULL)
    {
        printf("\e[0;31m%s: command not found222", argv[0]);
        node->shell->exit_code = 127; //exit code added
        exit(127);
    }
	if (ft_strcmp(node->cmd, "/usr/local/sbin/") == 0)
	{
		printf("\e[0;31m: command not found222");
		node->shell->exit_code = 127; //exit code added
		exit(127);
	}
	if (execve(node->cmd, argv, node->shell->env) == -1)
	{
		perror("execve failed\n");
		node->shell->exit_code = 1; //exit code added
		exit(EXIT_FAILURE);
	}
}

void	single_command(t_node *node, char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		handle_child_process(node, argv);
	else if (pid > 0)
	{
		wait(&status);
		unlink("fd_temp");
	}
	else
	{
		perror("Fork failed.\n");
		node->shell->exit_code = 1;
		exit(1);
	}
}

void	execute_other(t_node *node)
{
	char	**argv;

	if (node->is_pipe == 0)
	{
		argv = build_argv(node);
		single_command(node, argv);
		free_double((void **)argv);
	}
}

void	execute_builtin(t_node *command)
{
	if (!ft_strcmp(command->cmd, "pwd"))
		ft_pwd(command);
	else if (!ft_strcmp(command->cmd, "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command->cmd, "env"))
		ft_env(command);
	else if (!ft_strcmp(command->cmd, "cd"))
		ft_cd(command);
	else if (!ft_strcmp(command->cmd, "unset"))
		ft_unset(command);
	else if (!ft_strcmp(command->cmd, "exit"))
		ft_exit(command);
	else if (!ft_strcmp(command->cmd, "export"))
		ft_export(command);
}

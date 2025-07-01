/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:42:27 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/01 17:20:17 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_child_redirs_and_errors(char **result, t_node *node, char **argv)
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
		node->shell->exit_code = 127;
		free_double((void **)result);
		free_double((void **)argv);
		exit(127);
	}
	if (ft_strcmp(node->cmd, "/usr/local/sbin/") == 0)
	{
		printf("\e[0;31m: command not found222");
		node->shell->exit_code = 127;
		free_double((void **)result);
		free_double((void **)argv);
		exit(127);
	}
}

void	handle_child_process(char	**result, t_node *node, char **argv)
{
	handle_child_redirs_and_errors(result, node, argv);
	if (execve(node->cmd, argv, node->shell->env) == -1)
	{
		node->shell->exit_code = 1;
		free_double((void **)result);
		free_double((void **)argv);
		exit(EXIT_FAILURE);
	}
}

void	single_command(char	**result, t_node *node, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_child_process(result, node, argv);
	else if (pid > 0)
	{
		exit_code(node);
		unlink("fd_temp");
	}
	else
	{
		perror("Fork failed.\n");
		node->shell->exit_code = 1;
		free_double((void **)result);
		free_double((void **)argv);
		exit(1);
	}
}

void	execute_other(char	**result, t_node *node)
{
	char	**argv;

	if (node->is_pipe == 0)
	{
		argv = build_argv(node);
		single_command(result, node, argv);
		free_double((void **)argv);
	}
}

void	execute_builtin(t_node *command, char **result)
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
		ft_exit(command, result);
	else if (!ft_strcmp(command->cmd, "export"))
		ft_export(command);
}

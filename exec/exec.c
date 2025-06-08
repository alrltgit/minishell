/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:42:27 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/08 19:42:18 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_command(t_node *node, char **argv)
{
	pid_t	pid;
	int		status;
	t_redir *redir;

	pid = fork();
	if (pid == 0)
	{
		redir = node->redir_files;
		while (redir)
		{
			if (redir->type->stdin_redir == 1)
			{
				if (redirect_to_stdin(redir) == 1)
					exit(1);
			}
			else if (redir->type->stdout_redir == 1)
			{
				if (redirect_to_stdout(redir) == 1)
					exit(1);
			}
			redir = redir->next;
		}
		if (node->cmd == NULL)
		{
			printf("%s: command not found", argv[0]);
			exit(127);
		}
		if (execve(node->cmd, argv, node->shell->env) == -1)
		{
			perror("execve failed\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		wait(&status);
	else
	{
		perror("Fork failed.\n");
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
		free_arr(argv);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:42:27 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/09 13:32:40 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_command(t_node *node, char **argv)
{
	pid_t	pid;
	int		status;
	t_redir *redir;
	int		fd;

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
			else if (redir->type->heredoc_redir == 1)
            {
                if (heredoc(redir->file_name) == 1)
        			exit(1);
    
				fd = open("fd_temp", O_RDONLY);
				if (fd < 0)
					exit(1);
				dup2(fd, STDIN_FILENO);
				close(fd);
            }
			else if (redir->type->append_redir == 1)
			{
				if (append(redir) == 1)
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
	{
		wait(&status);
		unlink("fd_temp");
	}
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:49:18 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/14 13:01:03 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void single_command(t_node *node, char **argv)
{
	pid_t 	pid;
	int		status;

	pid = fork();
	if (pid == 0) // id of a child process is 0
	{
		// printf("EXEC OTHER PATH: %s\n", command->cmd);
		if (execve(node->cmd, argv, node->shell->env) == -1)
		{
			perror("execve failed\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0) // id of a parent process is unique, but it's always greater than 0
	{
		wait(&status);
		// printf("Child process finished with status: %d\n", status);
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

	/*when the command come here
	it will be checked if it is valid or not*/
	/*
		THINK ABOUT EDGE CASES
	*/
	// if (node->is_pipe == 1)
	// {
	// 	create_pipe(node, argv);
	// }
	if (node->is_pipe == 0)
	{
		argv = build_argv(node);
		// printf("argv[0]: %s\n", argv[0]);
		// printf("argv[1]: %s\n", argv[1]);
		single_command(node, argv);
		free_arr(argv);
	}
	// free_double((void **)argv);
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
	//else if (!ft_strcmp(command->cmd, "unset"))
		//ft_unset();
	//else if (!ft_strcmp(command->cmd, "exit"))
		//ft_exit();
	else if (!ft_strcmp(command->cmd, "export"))
		ft_export(command);
}

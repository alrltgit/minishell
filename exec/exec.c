
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:49:18 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/12 14:35:23 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_other(t_node *node)
{
	char	**argv;
	pid_t 	pid; // pid_t type is able to store id of a process
	int		status;

	pid = fork(); // creates a child process out of a parent process
	argv = build_argv(node);
	// printf("argv[0]: %s\n", argv[0]);
	// printf("argv[1]: %s\n", argv[1]);
	/*when the command come here
	it will be checked if it is valid or not*/
	/*
		THINK ABOUT EDGE CASES
	*/

	//NEEDS TO BE FORKED
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
	free_double((void **)argv);
}

void	execute_builtin(t_node *command)
{
	if (!ft_strcmp(command->cmd, "pwd"))
		ft_pwd(command);
	//else if (!ft_strcmp(command->cmd, "echo"))
		//ft_echo()
	else if (!ft_strcmp(command->cmd, "env"))
		ft_env(command);
	else if (!ft_strcmp(command->cmd, "cd"))
		ft_cd(command);
	//else if (!ft_strcmp(command->cmd, "unset"))
		//ft_unset();
	//else if (!ft_strcmp(command->cmd, "exit"))
		//ft_exit();
	//else if (!ft_strcmp(command->cmd, "export"))
		//ft_export();
}

/* void	recognize_command(t_node *command)
{
	char	*cmd;

	// what if it is not a command????
	cmd = command->cmd;
	if (is_validcommand)
		execute_other(command);
	else
		perror();
} */

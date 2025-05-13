
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

int count_arr_size(char **arr, int arr_count)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < arr_count)
	{
		j = 0;
		while (arr[j])
		{
			count++;
			j++;
		}
		count++;
		i++;
	}
	return (count);
}

char *concat_flags(t_node *node, int flags_size)
{
	char *flags;
	int i;
	int j;
	int k;

	flags = malloc(sizeof(char) * (flags_size + node->flags_count + 1));
	if (!flags)
		return (NULL);
	i = 0;
	k = 0;
	while (i < flags_size - 1)
	{
		j = 0;
		while (node->flags[i][j])
		{
			flags[k++] = node->flags[i][j++]; 
		}
		// if (i != flags_size - 2)
		// {
		// 	flags[k++] = ' ';
		// }
		i++;
	}
	flags[k] = '\0';
	return (flags);
}

char *concat_args(t_node *node, int args_size)
{
	char *args;
	int i;
	int j;
	int k;

	args = malloc(sizeof(char) * (args_size + node->args_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	k = 0;
	while (i < args_size - 1)
	{
		j = 0;
		while (node->args[i][j])
		{
			args[k++] = node->args[i][j++]; 
		}
		// if (i != args_size - 1)
		// {
		// 	args[k++] = ' ';
		// }
		i++;
	}
	args[k] = '\0';
	return (args);
}

char	**build_argv(t_node *node)
{
	char	**argv;
	// int		i;
	// int		j;
	int		flags_size;
	int		args_size;
	char	*flags;
	char 	*args;

	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return (NULL); //MAYBE YOU CAN SET STH FOR ERRCODE
	argv[0] = ft_strdup(node->cmd);
	if (!argv[0])
		return (NULL);
	flags_size = count_arr_size(node->flags, node->flags_count);
	args_size = count_arr_size(node->args, node->args_count);
	printf("args_size: %d\n", args_size);
	argv[1] = malloc(sizeof(char) * (flags_size + args_size + 1));
	if (!argv[1])
		return (NULL);
	flags = concat_flags(node, flags_size);
	printf("TEST\n");
	printf("flags: %s\n", flags);
	args = concat_args(node, args_size);
	printf("args: %s\n", args);
	argv[1] = ft_strcat(flags, args);
	printf("argv[1]: %s\n", argv[1]);
	argv[2] = NULL;
	free(flags);
	free(args);
	return (argv);
}

void	execute_other(t_node *node)
{
	char	**argv;
	pid_t 	pid; // pid_t type is able to store id of a process
	int		status;

	pid = fork(); // creates a child process out of a parent process
	argv = build_argv(node);
	printf("argv[0]: %s\n", argv[0]);
	printf("argv[1]: %s\n", argv[1]);
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
		printf("Child process finished with status: %d\n", status);
	}
	else
	{
		perror("Fork failed.\n");
		exit(1);
	}
	// free_double((void **)argv);
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

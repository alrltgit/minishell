/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:49:18 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/13 13:51:49 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**build_argv(t_node *command)
{
	char	**argv;
	int		i;
	int		j;

	argv = malloc(sizeof(char *) *
		(command->args_count + command->flags_count + 1));
	if (!argv)
		return (NULL); //MAYBE YOU CAN SET STH FOR ERRCODE
	i = 0;
	j = 0;
	while (j < command->args_count)
		argv[i++] = command->args[j++];
	j = 0;
	while (j < command->flags_count)
		argv[i++] = command->flags[j++];
	argv[i] = NULL;
	return (argv);
}

void	execute_other(t_node *command)
{
	char	**argv;

	argv = build_argv(command);
	/*when the command come here
	it will be checked if it is valid or not*/
	/*
		THINK ABOUT EDGE CASES
	*/

	
	//NEEDS TO BE FORKED
	printf("EXEC OTHER PATH: %s\n", command->cmd);
	if (execve(command->cmd, argv, command->shell->env) == 	-1)
	{
		perror("execute other execve error\n");
	}
	free_double((void **)argv);
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
	//else if (!ft_strcmp(command->cmd, "export"))
		//ft_export();
}

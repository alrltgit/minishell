/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:37:21 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/08 14:59:52 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_node *command)
{
	//char	*pwd;

	/*
		#just cd changes to home
		#cd + arg changes to arg directory
		#in parsing check arg is directory
		#arg count must be less than 2
	*/
	if (command->args_count > 2)
	{
		ft_putstr_fd("cd: too many arguments", 2);
		command->shell->errcode = 1;
		return ;
	}
	printf("BEFORE CHDIR : %s\n", value_from_key("PWD", command->shell));
	//when there is no arg (just cd)
	if (command->args_count == 0 &&
		chdir(value_from_key("HOME", command->shell)))
	{
		command->shell->errcode = 1;
		perror("cd");
	}
	printf("AFTER CHDIR: %s\n", value_from_key("PWD", command->shell));
	/* pwd = getcwd(NULL, 0);
	change_env_value("OLDPWD", pwd, command->shell);
	if (!ft_strcmp(command->args[0], "../") ||
		!ft_strcmp(command->args[0], ".."))
	{
		change_env_value("PWD", )
	} */

	


}
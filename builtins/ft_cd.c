/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:37:21 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/13 10:19:21 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_node *command)
{
	command->shell->errcode = 0;
	if (command->args_count > 1)
	{
		ft_putstr_fd("cd: too many arguments", 2);
		command->shell->errcode = 1;
		return ;
	}
	if (command->args_count == 1)
	{
		change_env_value("OLDPWD", getcwd(NULL, 0), command->shell);
		chdir(command->args[0]);
		change_env_value("PWD", getcwd(NULL, 0), command->shell);
		return ;
	}
	change_env_value("OLDPWD", getcwd(NULL, 0), command->shell);
	chdir(value_from_key("HOME", command->shell));
	change_env_value("PWD", getcwd(NULL, 0), command->shell);
}

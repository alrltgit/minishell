/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:37:21 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/13 16:16:10 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	for cd command, args_count will be max 1

	if we give multiple spaces after cd, 
	it should consider like without spaces
	so, trim spaces(it is trimmed in get_the_input)
*/

void	ft_cd(t_node *command)
{
	//char	*pwd;

	/*
		#just cd changes to home
		#cd + arg changes to arg directory
		#in parsing check arg is directory
		#arg count must be max 1

		if cd is without args,
		it will change directory to HOME
	*/
	command->shell->errcode = 0; //in case of success
	if (command->args_count > 1)
	{
		ft_putstr_fd("cd: too many arguments", 2);
		command->shell->errcode = 1; //it is true, checked with $?
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
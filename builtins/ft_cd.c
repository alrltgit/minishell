/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:37:21 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/30 13:13:24 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_err(t_node *command, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd("\e[0;31mminishell: cd: too many arguments\n", 2);
		command->shell->exit_code = 1;
		return (1);
	}
	else if (mode == 2)
	{
		ft_putstr_fd("\e[0;31mminishell: cd: ", 2);
		ft_putstr_fd(command->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		command->shell->exit_code = 1;
		return (2);
	}
	return (0);
}

void	check_init_oldpwd(t_shell *shell, char *oldpwd)
{
	if (index_from_key("OLDPWD", shell->env) == -1)
		add_key_val(shell, "OLDPWD=", oldpwd);
}

void	ft_cd(t_node *command)
{
	int		res;
	char	*oldpwd;

	if (command->args_count > 1 && print_err(command, 1))
		return ;
	oldpwd = getcwd(NULL, 0);
	if (command->args_count == 1 && ft_strcmp(command->args[0], "~") != 0
		&& ft_strcmp(command->args[0], "--") != 0)
	{
		res = chdir(command->args[0]);
		if (res != 0 && print_err(command, 2))
			return;
		check_init_oldpwd(command->shell, oldpwd);
		change_env_value("OLDPWD", oldpwd, command->shell);
		change_env_value("PWD", getcwd(NULL, 0), command->shell);
		return ;
	}
	else if (command->args_count == 0 || ft_strcmp(command->args[0], "~") == 0
		|| ft_strcmp(command->args[0], "--") == 0)
	{
		check_init_oldpwd(command->shell, oldpwd);
		change_env_value("OLDPWD", getcwd(NULL, 0), command->shell);
		chdir(value_from_key("HOME", command->shell));
		change_env_value("PWD", getcwd(NULL, 0), command->shell);
	}
}
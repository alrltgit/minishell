/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:30:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/30 13:29:18 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_node *cmd)
{
	char	*pwd;

	cmd->shell->exit_code = 0;
	pwd = value_from_key("PWD", cmd->shell);
	if (ft_strcmp(pwd, "") == 0)
	{
		cmd->shell->exit_code = 1;
		ft_putstr_fd("\e[0;31mminishell: pwd: unable to retrieve\n", 2);
	}
	else
		printf("%s\n", pwd);
}

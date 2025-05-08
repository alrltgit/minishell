/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:30:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/08 13:44:48 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_node *cmd)
{
	char	*pwd;

	cmd->shell->errcode = 0;
	pwd = value_from_key("PWD", cmd->shell);
	printf("PWD from custom func-> %s\n", pwd);
	if (!pwd)
	{
		cmd->shell->errcode = 1; //DOUBLE CHECK
		perror("pwd error"); //make it detailed with err codes
	}
}

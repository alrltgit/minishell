/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:30:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/22 17:37:01 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *Double check the errcode
 you might need to customize the perror
 */

void	ft_pwd(t_node *cmd)
{
	char	*pwd;

	cmd->shell->errcode = 0;
	pwd = value_from_key("PWD", cmd->shell);
	printf("%s\n", pwd);
	if (!pwd)
	{
		cmd->shell->errcode = 1;
		perror("pwd error");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:30:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/05 12:31:32 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	cmd->shell->errcode = 0;
	pwd = value_from_key("PWD", cmd->shell);
	//printf("PWD from custom func-> %s\n", pwd);
	if (!pwd)
		perror("pwd error"); //make it detailed with err codes
}

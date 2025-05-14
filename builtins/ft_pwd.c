/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:30:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/13 16:21:12 by alraltse         ###   ########.fr       */
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
	printf("PWD from custom func-> %s\n", pwd);
	if (!pwd)
	{
		cmd->shell->errcode = 1;
		perror("pwd error");
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:04:54 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/07 21:01:11 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	ft_env(t_unit *cmd)
{
	int		i;

	//if you input env and spaces it will execute env
	//but if you input env and any other character it will not execute
	//so handle the spaces and characters
	//or
	//take cmd already seperated
	if (count_vars(cmd->) != 1)
	{
		cmd->shell->errcode = 1;
		return;
	}
	i = -1;
	while (cmd->shell->env[++i])
	{
		printf("%s\n", cmd->shell->env[i]);
	}
} */
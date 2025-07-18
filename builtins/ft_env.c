/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:04:54 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/01 11:43:03 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_node *cmd)
{
	int	i;

	i = -1;
	while (cmd->shell->env[++i])
	{
		printf("%s\n", cmd->shell->env[i]);
	}
	cmd->shell->exit_code = 0;
}

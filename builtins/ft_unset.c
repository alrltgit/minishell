/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:35:45 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/04 13:26:36 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(char *key, t_shell *shell)
{
	int	index;
	int	env_size;

	index = index_from_key(key, shell->env);
	if (index == -1)
		return ;
	free(shell->env[index]);
	env_size = 0;
	while (shell->env[env_size])
		env_size++;
	while (index < env_size - 1)
	{
		shell->env[index] = shell->env[index + 1];
		index++;
	}
	shell->env[index] = NULL;
}

void	ft_unset(t_node *command)
{
	char	**split;
	char	c;
	int		i;

	if (ft_strcmp(command->fcmd, "unset") == 0)
		return ;
	split = split_args(command->fcmd);
	i = -1;
	while (split[1][++i])
	{
		c = split[1][i];
		if (c == '-' || c == ')' || c == '(' || c == '&' || c == '!')
		{
			ft_putstr_fd("\e[0;31mminishell: unset: syntax error\n", 2);
			command->shell->exit_code = 2;
			free_double((void **)split);
			return ;
		}
	}
	i = 0;
	while (split[++i])
	{
		update_env(split[i], command->shell);
	}
	free_double((void **)split);
}

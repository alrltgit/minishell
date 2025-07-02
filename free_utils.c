/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:17:55 by apple             #+#    #+#             */
/*   Updated: 2025/07/02 15:12:54 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	safe_free(char **temp, char **temp2, int mod)
{
	if (mod == 1)
	{
		if (*temp)
		{
			free(*temp);
			*temp = NULL;
		}
		return ;
	}
	else if (mod == 2)
	{
		if (*temp2)
		{
			free(*temp2);
			*temp2 = NULL;
		}
		return ;
	}
	else if (mod == 3)
	{
		safe_free(temp, NULL, 1);
		safe_free(NULL, temp2, 2);
		return ;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_exit(t_shell *shell)
{
	if (shell->cmds)
		iterate_free_nodes(shell->cmds);
	free_double((void **)shell->env);
	return ;
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_arr(shell->env);
	if (shell->cmds)
		free_node_list(shell->cmds);
	free(shell);
}

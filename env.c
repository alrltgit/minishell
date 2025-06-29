/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:24:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/29 11:08:57 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include <string.h>

/*check if the free double works properly*/
int	index_from_key(char *var_name, char **env_array)
{
	int		i;
	char	**var;
	int temp; // delete after debugging

	i = -1;
	while (env_array[++i])
	{
		var = ft_split(env_array[i], '=');
		temp = ft_strcmp(var_name, var[0]);
		if (temp == 0)
		{
			free_double((void **)var);
			return (i);
		}
		free_double((void **)var);
	}
	return (-1);
}

/*
	Handle what if the key is not valid	
*/
char	*value_from_key(char *var_name, t_shell *shell)
{
	int	index;

	if (ft_strcmp(var_name, "0") == 0)
		return ("minishell");
	index = index_from_key(var_name, shell->env);
	if (index == -1)
		return ("");
	return (ft_strchr(shell->env[index], '=') + 1);
}

void	copy_vars(char **ev, char ***env_array)
{
	int	i;

	i = -1;
	while (ev[++i])
		(*env_array)[i] = ft_strdup(ev[i]);
}

int	count_vars(char **ev)
{
	int	count;

	if (!ev)
		return (0);
	count = -1;
	while (ev[++count])
		;
	return (count);
}

void	init_env(char **ev, t_shell *shell)
{
	int	count;

	if (shell->env)
		free_double((void **)shell->env);
	count = count_vars(ev);
	shell->env = malloc((count + 1) * sizeof(char *));
	if (!shell->env)
		return ;
	copy_vars(ev, &shell->env);
	shell->env[count] = NULL;
	change_env_value("SHELL", "/bin/bash", shell);
}

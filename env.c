/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:24:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/25 14:41:56 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

/*check if the free double works properly*/
int	index_from_key(char *var_name, char **env_array)
{
	int		i;
	char	**var;

	i = -1;
	while (env_array[++i])
	{
		var = ft_split(env_array[i], '=');
		if (ft_strcmp(var_name, var[0]) == 0)
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

	index = index_from_key(var_name, shell->env);
	if (index == -1)
		return ("");
		// return (NULL);
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
	count = 0;
	while (ev[count])
		count++;
	return (count);
}

/*
	index = index_from_key("OLDPWD", shell->env);
	free(shell->env[index]);
	printf("Freeing env[%d]: %s\n", index, shell->env[index]);
	pwd = getcwd(NULL, 0);
	shell->env[index] = ft_strjoin("OLDPWD=", pwd);
*/
void	init_env(char **ev, t_shell *shell)
{
	int	count;

	count = count_vars(ev);
	shell->env = malloc((count + 1) * sizeof(char *));
	if (!shell->env)
		return ;
	copy_vars(ev, &shell->env);
	shell->env[count] = NULL;
	change_env_value("SHELL", "/bin/bash", shell);
}

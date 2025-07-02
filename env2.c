/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:19:19 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/02 15:06:43 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	change_env_value(char *var_name, char *new_value, t_shell *shell)
{
	int		index;
	char	*temp;

	if (!var_name)
		return (-1);
	index = index_from_key(var_name, shell->env);
	temp = ft_strjoin(var_name, "=");
	if (index != -1)
	{
		free(shell->env[index]);
		shell->env[index] = ft_strjoin(temp, new_value);
	}
	free(temp);
	return (1);
}

char	*key_from_index(int pos, t_shell *shell)
{
	char	**var;
	char	*key;

	var = ft_split(shell->env[pos], '=');
	if (!var)
		return (NULL);
	key = ft_strdup(var[0]);
	free_double((void **)var);
	return (key);
}

void	add_key_val(t_shell *shell, char *key, char *val)
{
	char	**temp;
	int		count;

	count = -1;
	while (shell->env[++count])
		;
	temp = malloc(sizeof(char *) * (count + 2));
	copy_vars(shell->env, &temp);
	temp[count] = ft_strjoin(key, val);
	temp[count + 1] = NULL;
	free_double((void **)shell->env);
	shell->env = temp;
}

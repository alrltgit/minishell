/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:24:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/08 16:53:01 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"


//set

//get_env_var

//need init_env in cd command cuz of pwd changing (actually e)
//so dont forget to update pwd
//WHEN OPEN THE TERMINAL AT THE FIRST TIME, THERE IS NO OLDPWD IN env OUTPUT
//SO SET OLDPWD AS CURRENT PWD WHILE INITIALIZING AT THE FIRST TIME

//handle
//->get value from variable (in case of <command> &ENVVARIABLE) -----DONE-----
//need to return the value after = (without =) ----DONE-----
//->set func that changes the value of specified env var

//ev is original env_array is copy

//> gets the index of specified env variable

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
			free_double((void **)var); //check is it properly working?
			return (i);
		}
		free_double((void **)var);
	}
	return (-1);
}

//it is used for pwd builtin
//we couldnt use getcwd cuz getcwd takes from real bash's env
//but we need to get from our own env
char	*value_from_key(char *var_name, t_shell *shell)
{
	int	index;

	index = index_from_key(var_name, shell->env);
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

void	init_env(char **ev, t_shell *shell)
{
	char	*pwd;
	int		count;
	int		index;

	count = count_vars(ev);
	shell->env = malloc((count + 1) * sizeof(char *));
	if (!shell->env)
		return ;
	copy_vars(ev, &shell->env);
	shell->env[count] = NULL;
	index = index_from_key("OLDPWD", shell->env);
	free(shell->env[index]); //free cuz oldpwd gonna get changed
	pwd = getcwd(NULL, 0);
	shell->env[index] = ft_strjoin("OLDPWD=", pwd);
	change_env_value("SHELL", "/bin/bash", shell);
	free(pwd);
}

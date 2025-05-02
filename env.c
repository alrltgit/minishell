/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:24:03 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/02 16:30:26 by apple            ###   ########.fr       */
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
//->get value from variable (in case of <command> &ENVVARIABLE)
//need to return the value after = (without =)
//

//ev is original env_array is copy

//> finds the index of specified env variable
int	find_ev_index(char *var_name, char **env_array)
{
	int		i;
	int		var_len;
	char	*sub_str;

	i = -1;
	var_len = ft_strlen(var_name);
	while (env_array[++i])
	{
		sub_str = ft_substr(env_array[i], 0, var_len);
		if (ft_strcmp(var_name, sub_str) == 0)
		{
			free(sub_str); //check is it properly working?
			return (i);
		}
	}
	return (-1);
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

char	**init_env(char **ev)
{
	char	**env_array;
	char	*pwd;
	int		count;
	int		index;

	count = count_vars(ev);
	env_array = malloc(count * sizeof(char *));
	copy_vars(ev, &env_array);
	env_array[count] = "\0";
	index = find_ev_index("OLDPWD", env_array);
	free(env_array[index]); //free cuz oldpwd gonna get changed
	pwd = getcwd(NULL, 0);
	env_array[index] = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	return (env_array);
}
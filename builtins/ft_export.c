/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:48 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/14 14:55:51 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
	if there is the variable already,
	update its value
	if there is not,
	create the var and set value and append
	to the end of env


	!! export name=             abc
	it will set empty line

	!! export name=abc def
	it will set just abc

	!!consider
	export name = adasda
	bash: export: `=': not a valid identifier

	so if arg[0]
*/

int	is_alphanumeric(char *key)
{
	int	i;

	i = -1;
	while (key[++i])
	{
		if (!(key[i] >= 'a' && key[i] <= 'z') &&
			!(key[i] >= 'A' && key[i] <= 'Z') &&
			!(key[i] >= '0' && key[i] <= '9'))
			return (0);
	}
	return (1);
}

/*
take till first = sign
and analyze the key
*/

char	*extract_key(char *input)
{
	int		key_len;
	char	*val;
	char	*key;

	val = ft_strchr(input, '=');
	key_len = ft_strlen(input) - ft_strlen(val);
	key = ft_split(ft_substr(input, 0, key_len), ' ')[1];
	return (key);
}

char	*process_value(char	*value)
{
	int	count;

	if (value[0] == ' ')
		return (" ");
	count = -1;
	while (value[++count] && value[count] != ' ')
		;
	return (ft_substr(value, 0, count));
}
/*
	if there is space after first = sign
	set empty line to value
*/

void	create_and_set_val(t_shell *shell, char *key, char *val)
{
	int		count;
	char	**new_env;
	char	*new_val;
	
	count = count_vars(shell->env);
	new_env = malloc((count + 2) * sizeof(char *));
	new_val = process_value(val);
	if (!new_env)
		return ;
	copy_vars(shell->env, &new_env);
	//free_double((void **)shell->env);
	new_env[count + 1] = ft_strjoin(key, new_val);
	new_env[count + 2] = NULL;
	init_env(new_env, shell);
	free_double((void **)new_env);
}
void	ft_export(t_node *command)
{
	char	*str1;
	char	*str2;
	char	*key;

	key = extract_key(rl_line_buffer);
	if (!is_alphanumeric(key))
	{
		str1 = ft_strcat("bash: ", rl_line_buffer);
		str2 = ft_strcat(str1, ": not a valid identifier\n");
		free(str1);
		ft_putstr_fd(str2, 2);
		free(str2);
		return ;
	}
	if (value_from_key(key, command->shell) != NULL)
		change_env_value(key,
			process_value(ft_strchr(rl_line_buffer, '=') + 1),
			command->shell);
	else
		create_and_set_val(command->shell, key,
				ft_strchr(rl_line_buffer, '=') + 1);
	free(key);
}
		
		// printf("VALUE-> %s\n", value_from_key(key, command->shell));
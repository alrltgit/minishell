/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:28:07 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/31 16:33:25 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Search flags, args. if you catch variable
	starts with $ sign, take the value from env
	and print.

	if there is variable with $ in command->cmd,
	print the value but add the error to the end

	if the variable with $ is in args or flags and
	it is not set in env, it will print empty line
	for ex: echo $abcdef

	for ex: $PATH
	bash: /nfs/homes/hceviz/bin:/usr/local/sbin:
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:
	/usr/games:/usr/local/games:/snap/bin: No such file or directory


	echo "-n" $PATH -> in this flag is valid
		and
	echo "-n $PATH" -> in this flag is not valid (takes it as arg)
	are not same!!

	check -n $PATH


	for $PATH $PWD, it will just give value of $PATH with error
	so, if cmd is expansion type, return the value with error and
	continue to shell loop

	if the expansion in the place of cmd is not exist and if it has
	something more after the expansion variable, execute them
	for ex: $abcde qwerty -> it will print qwerty: command not found
	for ex: $abcde echo abc -> it will print abc
	for ex: $PATH echo abc -> it will print value of $PATH with error
*/

//**arr will be reference of *arr */

/*
extract the expansion 

*/

int	is_alphanumeric(char a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')
		|| (a >= '0' && a <= '9') || a == '_')
		return (1);
	return (0);
}

/*
	return int.
	if there is valid expansion

	-$abcdef will be considered as flag
	so, scan everywhere for $ sign

	search for expansion variable, if there is expansion var,
	take it as long as it is alphanumeric (letters and numbers)

	if expansion var is exist, replace with its value from env
	if it is not exist, replace with empty string
*/

//it should be **command because we will pass by reference

/*
try with

	-$PATH echo abc -> - sign with paths with error
	$PATH echo abc -> paths with error
	echo abc $PATH -> abc with path WITHOUT error
	echo abc'$PATH' -> abc$PATH it doesnt replace expansion
	echo '"$PATH"' -> "$PATH" doesnt replace expansion
	echo $PATH"abc"
	echo $PATH'abc'
	echo $

	so if echo after valid expansion variable, add error
	and everything concatenated with expansion variable
	in examples it is -$PATH

	if echo is before than invalid expansion variable, 
	print everythin after echo

*/
//handle $? also cuz it is not visible in env

//IF IT IS IN SINGLE QUOTES, DONT REPLACE THE VALUE

//send the str to expand func if there is valid expansion,
//it will return the value, else null

char	*replace_var(t_shell *shell, char *str, char *var, int pos, int len, int quote)
{
	char	*tmp;
	int		j;

	j = -1;
	if (quote == 1)
		tmp = ft_substr(var, pos + 1, len - 1);
	else
		tmp = value_from_key(ft_substr(var, pos, len), shell);
	while (tmp && tmp[++j])
		str = update_str(str, tmp[j]);
	return (str);
}

char	*perfect(t_node *command, char **arr)
{
	int	in_sq;
	int	in_dq;
	int	i;
	int	j;
	int	len;
	char	*arr2 = *arr;
	char	*str;
	in_sq = 0;
	in_dq = 0;
	i = -1;
	str = NULL;

	while (arr2[++i])
	{
		if (arr2[i] == '\'' && in_dq == 0)
			in_sq = 1 - in_sq;
		if (arr2[i] == '"' && in_sq == 0)
			in_dq = 2 - in_dq;
		if (arr2[i] == '$' && in_sq == 0 && arr2[i + 1] != ' ' && arr2[i + 1] != '\0')
		{
			j = i;
			len = 0;
			while (is_alphanumeric(arr2[++j]))
				++len;
			str = replace_var(command->shell, str, arr2, i + 1, len, in_sq + in_dq);
			i += len;
		}
		else
			str = update_str(str, arr2[i]);
	}
	return (str);
}


/*
	when input is given it will go
	quote handling, expansion, execution

	EXPORT AND ECHO NEEDS IMPROVEMENTS
*/

void	process_exp(t_node *command)
{
	int		i;
	char	*temp;
	//printf("ENTERED PROCESS_EXP with \n");
	//print_node(command);
	i = -1;
	while (++i < command->args_count)
	{
		temp = ft_strdup(command->args[i]);
		free(command->args[i]);
		command->args[i] = ft_strdup(handle_quotes(perfect(command, &temp)));
	}
	i = -1;
	while (++i < command->flags_count)
	{
		temp = ft_strdup(command->flags[i]);
		free(command->flags[i]);
		command->flags[i] = ft_strdup(handle_quotes(perfect(command, &temp)));
	}
}

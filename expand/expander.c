/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:28:07 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/19 23:34:47 by apple            ###   ########.fr       */
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
		|| (a >= '0' && a <= '9') || a == '_' || a == '?')
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
	else if (var[pos] == '?')
		tmp = ft_itoa(shell->exit_code); //exit code added
	else
	{
		tmp = value_from_key(ft_substr(var, pos, len), shell);
		if (ft_strcmp(tmp, "") == 0)
			tmp = " ";
	}
	while (tmp && tmp[++j])
		str = update_str(str, tmp[j]);
	return (str);
}

char	*perfect(t_node *command, char *arr)
{
	int		in_sq;
	int		in_dq;
	int		i;
	int		j;
	int		len;
	char	*str;

	in_sq = 0;
	in_dq = 0;
	i = 0;
	str = NULL;

	if (!arr)
	{
		arr = update_str(arr, ' ');
		return (arr);
	}
	while (arr[i])
	{
		if (arr[i] == '\'' && in_dq == 0)
		{
			in_sq = 1 - in_sq;
		}
		if (arr[i] == '"' && in_sq == 0)
		{
			in_dq = 2 - in_dq;	
		}
		if (arr[i] == '$' && in_sq == 0 && arr[i + 1] != ' ' && arr[i + 1] != '\0')
		{
			j = i;
			len = 0;
			if (arr[i + 1] == '?')
			{
				str = replace_var(command->shell, str, arr, i + 1, 1, in_sq + in_dq);
				i += 2;
				continue;
			}
			while (is_alphanumeric(arr[++j]))
				++len;
			//print_node(command);
			str = replace_var(command->shell, str, arr, i + 1, len, in_sq + in_dq);
			i += len;
		}
		else
			str = update_str(str, arr[i]);
		i++;
	}
	return (str);
}

int	fake_perfect(char *arr)
{
	int	i = 0;
	int	in_sq = 0;
	int	in_dq = 0;

	while (arr[i])
	{
		if (arr[i] == '\'' && in_dq == 0)
			in_sq = !in_sq;
		else if (arr[i] == '"' && in_sq == 0)
			in_dq = !in_dq;
		i++;
	}
	if (in_sq || in_dq)
		return (0); // Unclosed quote
	return (1); // All quotes closed
}
/*
	when input is given it will go
	quote handling, expansion, execution

	EXPORT AND ECHO NEEDS IMPROVEMENTS
*/

/* if the str has syntax error it returns the str.
if everything is okay, it returns null*/
char	*process_exp(char **result, t_node *unit)
{
	int		i;
	char	*temp;
	char	*temp2;

	printf("result[0] = %s\n", result[0]);
	if (result[0])
	{
		if (!fake_perfect(result[0]))
			return (result[0]);
		temp = perfect(unit, result[0]);
		if (ft_strcmp(temp, " ") == 0)
			return ("");
		else
			result[0] = ft_strdup(handle_quotesv2(perfect(unit, temp)));
	}
	printf("result[0] = %s\n", result[0]);
	i = 0;
	while (result[++i])
	{
		//printf("before exp -> %s\n", result[i]);
		if (!fake_perfect(result[i]))
			return (result[i]);
		temp = ft_strdup(result[i]);
		temp2 = perfect(unit, temp);
		if (ft_strcmp(temp2, "") == 0)
		{
			result[i] = ft_strdup("");
			++i;
			free(temp2);
			free(temp);
			continue;
		}
		result[i] = ft_strdup(handle_quotesv2(temp2));
		//printf("after exp -> %s\n", result[i]);
		free(temp);
	}
	return (NULL);
}

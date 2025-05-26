/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:28:07 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/26 13:49:37 by hceviz           ###   ########.fr       */
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

char	*replace_var(t_shell *shell, char **arr, int pos, int len, int in_squote)
{
	char	*l_half;
	int		i;
	char	*var;
	char	*f_half;
	char	*real_var;
	char	*realarr = *arr;
	//"'$PATH'"
	//pos is index of P
	if (in_squote == 1)
		return (*arr);
	var = ft_substr(realarr, pos, len);
	printf("DEBUG1 VAR -> %s\n", var);
	i = -1;
	//Till "' added into f_half (dont add $)
	// f_half = NULL;
	f_half = ft_substr(realarr, 0, pos - 1);
	printf("F_HALF -> %s\n", f_half);
	real_var = ft_strdup(value_from_key(var, shell));
	printf("DEBUG2 REAL_VAR -> %s\n", real_var);
	i = pos + len;
	// l_half = NULL;
	l_half = ft_strdup(realarr + i);
	printf("L_HALF -> %s\n", l_half);
	//ft_strcat(f_half, ft_strcat(real_var, l_half));
	/* free(*arr);
	*arr = ft_strdup(realarr); */
	realarr = ft_strcat(f_half, ft_strcat(real_var, l_half));
	printf("DEBUG3 REALARR-> %s\n", realarr);
	return (realarr);
	// printf("DEBUG4 NODE ARG-> %s\n", shell->cmds->args[0]);
}

char	*perfect(t_node *command, char **arr)
{
	int	in_sq;
	int	in_dq;
	int	i;
	int	j;
	int	len;
	char	*arr2 = *arr;
	in_sq = 0;
	in_dq = 0;
	i = -1;
	//"'$PATH'"
	//printf("ARRRRR %s\n", arr2);
	while (arr2[++i])
	{
		if (arr2[i] == '$' && is_alphanumeric(arr2[i + 1]))
		{
			j = i;
			len = 0;
			while (is_alphanumeric(arr2[++j]))
				++len;
			printf("POS -> %d\n", i + 1);
			printf("VALUE IN THE POSITION -> %c\n", arr2[i + 1]);
			printf("QUOTE MODE -> %d\n", in_dq + in_sq);
			arr2 = replace_var(command->shell, &arr2, i + 1, len, in_sq + in_dq);
		}
		if (arr2[i] == '\'' && in_dq == 0)
			in_sq = 1 - in_sq;
		if (arr2[i] == '"' && in_sq == 0)
			in_dq = 2 - in_dq;
	}
	return (arr2);
	/* free(arr);
	(*arr) = ft_strdup(arr2);
	free(arr2); */
}


void	process_exp(t_node *command)
{
	int		i;
	char	*temp;
	printf("ENTERED PROCESS_EXP with \n");
	print_node(command);
	i = -1;
	while (++i < command->args_count)
	{
		temp = ft_strdup(command->args[i]);
		free(command->args[i]);
		command->args[i] = ft_strdup(perfect(command, &temp));
		printf("DEBUG4 NODE ARG %d -> %s\n", i, command->args[i]);
	}
	i = -1;
	while (++i < command->flags_count)
	{
		command->flags[i] = perfect(command, &command->flags[i]);
	}
}

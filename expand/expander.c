/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:28:07 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/22 17:01:31 by hceviz           ###   ########.fr       */
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
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') ||
		(a >= '0' && a <= '9') || a == '_')
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

	so if echo after valid expansion variable, add error
	and everything concatenated with expansion variable
	in examples it is -$PATH

	if echo is before than invalid expansion variable, 
	print everythin after echo

*/
char	*expand_var(t_shell *shell, char *var)
{
	int	in_single;
	int	in_double;
	int	i;

	

	
}


//handle $? also cuz it is not visible in env

//IF IT IS IN SINGLE QUOTES, DONT REPLACE THE VALUE

//send the str to expand func if there is valid expansion,
//it will return the value, else null
void	search_expansion(t_node **command)
{
	int	i;
	int	j;
	char	*var;

	i = -1;
	while (++i < (*command)->args_count)
	{
		j = -1;
		while ((*command)->args[i][++j])
		{
			var = expand_var((*command)->shell, (*command)->args[i]);
			if ((*command)->args[i][j])
			if ((*command)->args[i][j] == '$')
			{
				replace_expansion((*command)->shell, &(*command)->args[i]);
				break;
			}
		}
	}
}

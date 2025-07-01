/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:28:07 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/01 18:45:01 by apple            ###   ########.fr       */
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

char	*handle_dollar(t_node *cmd, char *str, char *arr, int *i, int qte)
{
	int		j;
	int		len;

	j = *i;
	len = 0;
	if (arr[*i + 1] == '?')
	{
		str = replace_var(cmd->shell, str, arr, *i + 1, 1, qte);
		*i += 1;
		return (str);
	}
	while (is_alphanumeric(arr[++j]))
		++len;
	str = replace_var(cmd->shell, str, arr, *i + 1, len, qte);
	*i += len;
	return (str);
}

char	*iterate_and_replace(t_node *command, char *arr)
{
	int		in_sq;
	int		in_dq;
	int		i;
	char	*str;

	in_sq = 0;
	in_dq = 0;
	i = -1;
	str = NULL;
	(void) ((!arr) && (update_str(arr, ' ')));
	while (arr[++i])
	{
		if (arr[i] == '\'' && !in_dq)
			in_sq = 1 - in_sq;
		else if (arr[i] == '"' && !in_sq)
			in_dq = 2 - in_dq;
		else if (arr[i] == '$' && !in_sq && is_alphanumeric(arr[i + 1]))
		{
			str = handle_dollar(command, str, arr, &i, in_sq + in_dq);
			continue ;
		}
		else
			str = update_str(str, arr[i]);
	}
	return (str);
}

char	*process_exp3(char ***result, t_node *unit, char **temp, char **temp2)
{
	int	i;

	i = 0;
	while ((*result)[i] && (*result)[++i])
	{
		if (!fake_perfect((*result)[i]))
			return ((*result)[i]);
		*temp = ft_strdup((*result)[i]);
		*temp2 = iterate_and_replace(unit, *temp);
		if ((*temp2) == NULL || (*temp2)[0] == '\0')
		{
			free((*result)[i]);
			(*result)[i] = ft_strdup("");
			free(*temp2);
			free(*temp);
			continue ;
		}
		free((*result)[i]);
		(*result)[i] = handle_quotesv2(*temp2);
		free(*temp);
	}
	return (NULL);
}

char    *process_exp2(char ***result, t_node *unit, char **temp)
{
    int count;
    count = -1;
    while ((*result)[++count])
        ;
    if ((*result)[0])
    {
        if (!fake_perfect((*result)[0]) || ((((*result)[0][0] == '"' && (*result)[0][1] == '"')
        || ((*result)[0][0] == '\'' && (*result)[0][1] == '\'')) && !(*result)[2]))
            return ((*result)[0]);
        *temp = iterate_and_replace(unit, (*result)[0]);
        if ((*temp) == NULL || (*temp)[0] == '\0')
        {
            delete_token_and_shift(*result, &count, 0);
            free(*temp);
            return (process_exp(*result, unit));
        }
        else
        {
            free((*result)[0]);
            (*result)[0] = handle_quotesv2(*temp);
        }
    }
    return (NULL);
}

char	*process_exp(char **result, t_node *unit)
{
	char	*temp;
	char	*temp2;
	char	*res;

	res = process_exp2(&result, unit, &temp);
	if (res != NULL)
		return (res);
	free(res);
	res = process_exp3(&result, unit, &temp, &temp2);
	if (res != NULL)
		return (res);
	return (NULL);
}

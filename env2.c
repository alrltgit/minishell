/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:19:19 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/04 14:08:04 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//in bash after reopening the terminal env gets refreshed
//also in subshell, env gets refreshed
//if the value is in quotes, it will be assigned without quotes -> SHLVL="abc" -> SHLVL=abc


//consider SHLVL='123" or SHLVL="123'
//add quote detection
//maybe you can return -1 to trigger > operator to close the quote
// > operator just close with started quote, otherwise it takes it as an input and all input will be in the history
/*
for ex
echo '"'123'
> "
> "
> "
> "
> '
"123
"
"
"
"

*/

/*
SHLVL="'     123''" -> it accepts this value but (it consider it as string)
SHLVL=    123 -> it doesnt accept

*/


//HANDLE THE AFFECT OF $ SIGN
//WHAT IF IT INITIALIZE VARIABLE WITH $
//OR IF IT TRY TO REACH ENV VAR WITH $

int	change_env_value(char *var_name, char *new_value, t_shell *shell)
{
	int		index;
	char	*temp;

	if (!var_name)
		return (-1);
	index = index_from_key(var_name, shell->env);
	//process with handle_quote -> handle_quote(&new_value);
	//if quote(s) needs to be closed return 0 otherwise 1
	temp = ft_strjoin(var_name, "=");
	free(shell->env[index]); //free space for new value
	shell->env[index] = ft_strjoin(temp, new_value);
	free(temp);
	return (1);
}

char	*key_from_index(int	pos, t_shell *shell)
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

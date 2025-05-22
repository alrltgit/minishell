/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:35:45 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/22 17:07:01 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
	with unset you will remove the whole line of given
	key. for ex if i do unset SHLVL, it will delete whole line
	SHLVL and its value from env

	if the given key is not valid, do nothing


	unset $SHLVL should do nothing as original bash

	if i do unset SHLVL DISPLAY, it will remove both of them

	so the formula is 

	if rl_line_buffer[0] is not flag,
	keep going to check args.
	if arg is not valid, do nothing
	if arg is valid, remove from env and update env
	apply it to all args because unset can take multiple args

	unset SHLVL | echo abc
	it just prints echo, DOESNT remove SHLVL
*/

/*
	unset -fl -> invalid -l
	unset -l ->invalid -l
	unset -fvnl -> invalid -l
	unset - -> does nothing

	unset SHLVL -aksjdfklasj DISPLAY
	if first arg doesnt throw error, keep going
*/
void	print_environment(t_shell *shell);

void	update_env(char *key, t_shell *shell)
{
	int	index;
	int	env_size;

	index = index_from_key(key, shell->env);
	if (index == -1)
		return;
	free(shell->env[index]);
	env_size = 0;
    while (shell->env[env_size])
        env_size++;
    while (index < env_size - 1)
    {
        shell->env[index] = shell->env[index + 1];
        index++;
    }
	shell->env[index] = NULL;
}

void	ft_unset(t_node *command)
{
	char	**split;
	char	c;
	int		i;

	split = split_args(rl_line_buffer);
	c = split[1][0];
	if (c == '-' || c == ')' || c == '(' || c == '&' || c == '!')
	{
		printf("bash: unset: syntax error!\n");
		free_double_n((void **)command->args, command->args_count);
		free_double_n((void **)command->flags, command->flags_count);
		return;
	}
	i = 0;
	while (split[++i])
		update_env(split[i], command->shell);
}

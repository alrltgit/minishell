/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:28:07 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/17 16:45:17 by hceviz           ###   ########.fr       */
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
*/
void	replace_expansion(t_shell *shell, char **arr)
{
	char	*value;

	free(*arr);
	value = value_from_key(ft_strchr(*arr, '$') + 1, shell);
	printf("VALUE-> %s\n", value);
	if (value == NULL)
	{
		*arr = ft_strdup("\n");
		return ;
	}
	value = ft_strdup(value);
}

void	search_expansion(t_node *command)
{
	int	i;

	i = -1;
	while (command->args[++i])
	{
		if (command->args[i][0] == '$')
			replace_expansion(command->shell, &command->args[i]);
		else if (command->flags[i][0] == '$')
			replace_expansion(command->shell, &command->flags[i]);
		else if (command->cmd[0] == '$')
		{
			printf("bash: ");
			replace_expansion(command->shell, &command->cmd);
			printf(" No such file or directory\n");
			break;
		}
	}
}

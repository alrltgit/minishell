/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:46:53 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/01 12:30:43 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_seperated_err(char *key, char *val, int mod)
{
	char	*keyval;

	if (mod == 1)
	{
		printf(EXPERR, key);
		printf(EXPERR, val);
	}
	else if (mod == 2)
	{
		keyval = ft_strcat(key, val);
		printf(EXPERR, keyval);
		free(keyval);
	}
	else if (mod == 4)
		printf(EXPERR, val);
}

int	value_syntax_ok(char *val)
{
	int	i;

	i = -1;
	while (val[++i])
	{
		if (val[i] == '!' || val[i] == '('
			|| val[i] == ')' || val[i] == ';')
			return (0);
	}
	return (1);
}

/*
	if there is space after first = sign
	set empty line to value
*/
void	create_and_set_val(t_shell *shell, char *key, char *val)
{
	int		count;
	char	**new_env;

	count = count_vars(shell->env);
	new_env = malloc((count + 2) * sizeof(char *));
	if (!new_env)
		return ;
	copy_vars(shell->env, &new_env);
	new_env[count] = ft_strjoin(key, val);
	new_env[count + 1] = NULL;
	init_env(new_env, shell);
	free_double((void **)new_env);
}

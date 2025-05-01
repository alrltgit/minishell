/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:31 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/01 15:04:29 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	shell_loop(t_shell *shell)
{
	while (1)
	{
		//checkargs
		//process
		//execute
	}

}

int main(int ac, char **av, char **ev)
{
	t_shell	shell;
	(void)av;

	if (ac != 1)
		return (ft_putstr_fd("Wrong arguments!\n", 2), 1);
	shell.env = init_env(ev);

	for (int i = 0; shell.env[i] != NULL; i++)
	{
		printf("%s\n", ev[i]);

	}
	printf("%d\n", find_ev_index("SESSION_MANAGER", shell.env));
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:31 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/03 16:48:22 by alraltse         ###   ########.fr       */
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

int	shell_loop(t_shell shell)
{
	char *rl;
	
	(void) shell;
	rl = NULL;
	while (1)
	{
		// prompt
		if (create_prompt(rl) == 1)
			return (1);

		//checkargs
		//process
		//execute
	}
	free(rl);
	return (0);
}

int main(int ac, char **av, char **ev)
{
	t_shell	shell;
	(void)av;

	if (ac != 1)
		return (ft_putstr_fd("Wrong arguments!\n", 2), 1);
	shell.env = init_env(ev);
	shell_loop(shell);
	// for (int i = 0; shell.env[i] != NULL; i++)
	// {
	// 	printf("%s\n", ev[i]);

	// }
	// printf("%d\n", find_ev_index("SESSION_MANAGER", shell.env));
    return (0);
}
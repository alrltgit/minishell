/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:31 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/02 18:08:04 by apple            ###   ########.fr       */
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

void	shell_loop()
{
	while (1)
	{
		// prompt
		char *rl = readline("> ");
		ft_printf("%s", rl);
		//checkargs
		//process
		//execute
	}
}

int main(int ac, char **av, char **ev)
{
	t_shell	shell;
	(void)av;

	if (ac < 1)
		return (ft_putstr_fd("Wrong arguments!\n", 2), 1);
	shell.env = init_env(ev);
	shell_loop();
	// prompt
	// char *rl = readline("> ");
	// ft_printf("%s", rl);
	// for (int i = 0; shell.env[i] != NULL; i++)
	// {
	// 	printf("%s\n", ev[i]);

	// }
	// printf("%d\n", find_ev_index("SESSION_MANAGER", shell.env));
    return (0);
}
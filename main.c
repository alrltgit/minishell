/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:31 by alraltse          #+#    #+#             */
/*   Updated: 2025/07/02 15:18:26 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	rl_exit(t_shell *shell)
{
	printf("exit\n");
	free_double((void **)shell->env);
	exit(0);
}

void	cwd_err(t_shell *shell)
{
	perror("minishell: getcwd");
	shell->exit_code = 1;
}

void	shell_loop(t_shell *shell)
{
	char	*rl;
	char	*pwd;

	shell->exit_code = 0;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			cwd_err(shell);
			break ;
		}
		signal(SIGINT, activate_ctrlc);
		rl = readline(PROMPT);
		signal(SIGINT, deactivate_ctrlc);
		if (!rl)
			rl_exit(shell);
		read_the_input(rl, shell);
		add_history(rl);
		safe_free(&rl, &pwd, 3);
	}
	free(pwd);
	free_exit(shell);
}

int	main(int ac, char **av, char **ev)
{
	t_shell	shell;

	ft_memset(&shell, 0, sizeof(shell));
	(void)av;
	if (ac != 1)
		return (ft_putstr_fd("Wrong arguments!\n", 2), 1);
	init_env(ev, &shell);
	shell_loop(&shell);
	free_exit(&shell);
	return (0);
}

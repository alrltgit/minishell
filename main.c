/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:31 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/22 19:50:46 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


//in bash echo ~ prints home folder (/nfs/homes/username)
// also cd ~ changes directory to home folder


void	print_node(t_node *command)
{
	int	i;

	i = -1;
	if (command->cmd)
		printf("CMD: %s // %p\n", command->cmd, (void *)command->cmd);
	while (++i < command->flags_count)
		printf("FLAG %d-> %s // %p\n", i, command->flags[i], (void *)command->flags[i]);
	i = -1;
	while (++i < command->args_count)
		printf("ARG %d-> %s // %p\n", i, command->args[i], (void *)command->args[i]);
}
void	print_environment(t_shell *shell) //delete at the end
{
	char	**key;
	/* for (int i = 0; shell->env[i] != NULL; i++)
	{
		key = ft_split(shell->env[i], '=');
		printf("%d %s\n", index_from_key(key[0], shell->env), shell->env[i]);
		free_double((void **)key);
	} */
	//below it prints the changed env
	for (int i = 0; shell->env[i] != NULL; i++)
	{
		key = ft_split(shell->env[i], '=');
		// printf("%d %s\n", index_from_key(key[0], shell->env), shell->env[i]);
		free_double((void **)key);
	}
	//printf("%d\n", index_from_key("SHLVL", shell->env));
}


/*
 NO NEED TO HANDLE UNCLOSED QUOTES!!!
 AND ALSO SPECIAL CHARACTERS
*/
void	shell_loop(t_shell *shell)
{
	char	*rl;
	char	*pwd;

	shell->exit_code = 0;
	signal(SIGQUIT, SIG_IGN); //ignore ctrl-'\'
	//shell->cmds = NULL;
	while (1)
	{
		//handle the cases when path changed
		//DONT FORGET TO ADD SIGINT HANDLING DURING COMMAND EXEC
		//CTRL-D JUST EXITS IN THESE CASES
		//->HERE-DOC (IT PRINTS EXIT AFTER EXITING) (EOF)
		//->WHILE WAITING FOR INPUT
		pwd = getcwd(NULL, 0);
		if (!pwd)
        {
            perror("minishell: getcwd");
			shell->exit_code = 1;
            break;
        }
		signal(SIGINT, activate_ctrlc);
		rl = readline(PROMPT);
		signal(SIGINT, deactivate_ctrlc);
		if (!rl)
		{
			printf("exit\n");
			//conditional jump was here
			free_double((void **)shell->env);
			exit(0);
		}
		//ft_export line 113 changed cuz of expansion updates on env
		read_the_input(rl, shell);
		//print_environment(shell);
		add_history(rl);
		free(rl);
		free(pwd);
	}
	free(pwd);
	free_exit(shell);
}

int main(int ac, char **av, char **ev)
{
	t_shell	shell;
	(void)av;
	
	if (ac != 1)
		return (ft_putstr_fd("Wrong arguments!\n", 2), 1);
	init_env(ev, &shell);
	//handle $variable expansion
	shell_loop(&shell);
	//free_double((void **)shell.env);
    return (0);
}

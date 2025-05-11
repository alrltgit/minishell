/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:31 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/11 15:21:48 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


//in bash echo ~ prints home folder (/nfs/homes/username)
// also cd ~ changes directory to home folder

void	print_environment(t_shell *shell) //delete at the end
{
	char	**key;
	for (int i = 0; shell->env[i] != NULL; i++)
	{
		key = ft_split(shell->env[i], '=');
		printf("%d %s\n", index_from_key(key[0], shell->env), shell->env[i]);
		free_double((void **)key);
	}
	//below it prints the changed env
	for (int i = 0; shell->env[i] != NULL; i++)
	{
		key = ft_split(shell->env[i], '=');
		printf("%d %s\n", index_from_key(key[0], shell->env), shell->env[i]);
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

	signal(SIGQUIT, SIG_IGN); //ignore ctrl-'\'
	while (1)
	{
		//handle the cases when path changed
		//DONT FORGET TO ADD SIGINT HANDLING DURING COMMAND EXEC
		//CTRL-D JUST EXITS IN THESE CASES
		//->HERE-DOC (IT PRINTS EXIT AFTER EXITING) (EOF)
		//->WHILE WAITING FOR INPUT
		pwd = getcwd(NULL, 0);
		signal(SIGINT, activate_ctrlc);
		//NO NEED TO UPDATE PROMPT PATH AFTER CD
		rl = readline("minishell$ ");
		read_the_input(rl, shell);
		// 	continue ;
		signal(SIGINT, deactivate_ctrlc);
		//if there is different pwd, update it
		//checkargs
		//process
		//execute
		add_history(rl);
		//printf("%s\n", rl_line_buffer);
	}
	free(pwd);
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
	/* char *path = "/bin/echo";
	char *args[] = { "echo", "'helloworld" , NULL };
	execve(path, args, ev); */
	//print_environment(&shell);
	//free_double((void **)shell.env);
    return (0);
}
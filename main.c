/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:31 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/02 16:59:53 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


//in bash echo ~ prints home folder (/nfs/homes/username)
// also cd ~ changes directory to home folder


//COMPLETE IT
/* int	handle_quotes(char **str) //it will modify from the original value
{
	int	head;
	int	tail;

	head = 0;
	tail = ft_strlen(str);
	
} */

void	print_environment(t_shell *shell) //delete at the end
{
	char	**key;
	for (int i = 0; shell->env[i] != NULL; i++)
	{
		key = ft_split(shell->env[i], '=');
		printf("%d %s\n", index_from_key(key[0], shell->env), shell->env[i]);
		free_double((void **)key);
	}
	change_env_value("ZDOTDIR", "HASAN", shell);
	//below it prints the changed env
	for (int i = 0; shell->env[i] != NULL; i++)
	{
		key = ft_split(shell->env[i], '=');
		printf("%d %s\n", index_from_key(key[0], shell->env), shell->env[i]);
		free_double((void **)key);
	}
	//printf("%d\n", index_from_key("SHLVL", shell->env));
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/*
	It just sets user@user:~
	rest will be dependent on functions
*/
char	*set_prompt(t_shell *shell)
{
	char	*prompt;
	char	*user;
	char	*temp;
	char	*temp2;

	user = value_from_key("USER", shell);
	temp = ft_strjoin(user, "@");
	temp2 = ft_strjoin(user, ":~");
	prompt = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (prompt);
}

void	shell_loop(t_shell *shell)
{
	char	*rl;
	char	*prompt;
	char	*pwd;

	prompt = set_prompt(shell);
	//for prompt the structure will be
	//at the start of shell username@username:~$
	//for ex user@user:~/Desktop/minishell$
	//path side is gonna be changed in related commands
	//at the beginning it starts from HOME (~)
	//when it is at home it shows user@user:~$
	//changed to Desktop -> user@user:~/Desktop$
	//so path is placed between ~ and $ sign
	while (1)
	{
		//handle the cases when path changed
		pwd = getcwd(NULL, 0);
		rl = readline(ft_strcat(prompt, "$ "));
		//checkargs
		//process
		//execute

	}
	free (prompt);
	free(pwd);
}

int main(int ac, char **av, char **ev)
{
	t_shell	shell;
	(void)av;

	if (ac != 1)
		return (ft_putstr_fd("Wrong arguments!\n", 2), 1);
	shell.env = init_env(ev);
	shell_loop(&shell);
	//print_environment(&shell);
	free_double((void **)shell.env);

    return (0);
}
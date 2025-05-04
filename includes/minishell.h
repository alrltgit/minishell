/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/03 16:19:36 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#define PS1 "> "

typedef struct	s_shell
{
	char	**env;
	
}	t_shell;

//main.c
int	ft_strcmp(char *s1, char *s2);


//env.c
char	**init_env(char **ev);
int		find_ev_index(char *var_name, char **env_vars);

//prompt.c
int create_prompt(char *rl);

#endif
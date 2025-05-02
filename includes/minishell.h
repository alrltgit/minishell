/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/02 16:59:54 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#include <malloc.h> //delete


typedef struct	s_shell
{
	char	**env;
	char	*prompt;
	
}	t_shell;


//typedef struct	s_cmd
//main.c
int	ft_strcmp(char *s1, char *s2);


//env.c
char	**init_env(char **ev);
int		index_from_key(char *var_name, char **env_array);
char	*value_from_key(char *var_name, t_shell *shell);

//env2.c
int		change_env_value(char *var_name, char *new_value, t_shell *shell);
char	*key_from_index(int	pos, t_shell *shell);

#endif
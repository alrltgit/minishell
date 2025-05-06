/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/06 14:20:05 by alraltse         ###   ########.fr       */
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

typedef struct s_lexer
{
	char *data;
	struct s_lexer *next;
}	t_lexer;

typedef struct s_node
{
	char *cmd;
	char **flags;
	char **args;
	int flags_count;
	int args_count;
}	t_node;

typedef struct s_unit
{
	t_node *data;
	struct s_ast *next;
}	t_unit;

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
int create_prompt(char *rl, t_lexer *lexers);

//lexing & parsing
char **split_args(char *str);
void read_the_input(char *rl, t_lexer *lexers);
t_lexer *add_node_to_end(t_lexer **head, char *data);
t_lexer *add_lexers_to_list(char **rl);

//free
void free_arr(char **arr);

//find_commands
char *find_command_path(char *input, t_unit *unit, int *cmd_is_found);
// char **get_path();
char *ft_strconcat(char *path, char *cmd);
// void find_operators(t_lexer *lexers, t_node *ast);

//find_glags.c
int count_flags(t_lexer *input);
void find_flags(t_lexer *temp, t_unit *unit, int *i);

#endif
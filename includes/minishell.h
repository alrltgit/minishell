/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/06 19:26:29 by apple            ###   ########.fr       */
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
	struct s_unit *next;
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

// parsing
char **split_args(char *str);
void read_the_input(char *rl, t_lexer *lexers);
t_lexer *add_node_to_end(t_lexer **head, char *data);
t_lexer *add_lexers_to_list(char **rl);

//free
void free_arr(char **arr);

// split the linked list
void add_cmds_flags_to_linked_list(t_lexer *input, t_unit **unit);

// parse_input
// fill_unit_linked_list
t_unit *add_unit_to_end(t_unit **head);

// find_cmd.c
void find_command_path(char *input, t_unit *unit, int *cmd_is_found);
char *ft_strconcat(char *path, char *cmd);

// find_flags.c
int count_flags(t_lexer *input);
void find_flags(t_lexer *temp, t_unit *unit, int *i);

// find_args.c
int count_args(t_unit *unit, t_lexer *input);
void find_args(t_unit *unit, t_lexer *temp, int *i);
#endif
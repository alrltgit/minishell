/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/07 16:08:36 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#define PS1 "> "

typedef struct s_node t_node;

typedef struct	s_shell
{
	char	**env;
	char	*prompt;
	t_node	*cmds;
	int		errcode;
}	t_shell;

typedef struct s_node
{
	t_shell	*shell;
	char *cmd;
	char **flags;
	char **args;
	int flags_count;
	int args_count;
	t_node *next;
}	t_node;


//typedef struct	s_cmd
//main.c
int	ft_strcmp(char *s1, char *s2);

//env.c
void	init_env(char **ev, t_shell *shell);
int		index_from_key(char *var_name, char **env_array);
char	*value_from_key(char *var_name, t_shell *shell);
int		count_vars(char **ev);

//env2.c
int		change_env_value(char *var_name, char *new_value, t_shell *shell);
char	*key_from_index(int	pos, t_shell *shell);

//signal.c
void	activate_ctrlc(int sig);
void	deactivate_ctrlc(int sig);

//BUILTINS
void	ft_pwd(t_node *command);
void	ft_env(t_node *command);

//ALINA
//prompt.c
int create_prompt(char *rl, t_shell *shell);

// parsing
char **split_args(char *str);
void read_the_input(char *rl, t_shell *shll);

//free
void free_arr(char **arr);

// split the linked list
void add_cmds_flags_to_linked_list(char **result, t_node **unit);

// parse_input
// fill_unit_linked_list
t_node *add_unit_to_end(t_node **head);
t_node *create_unit();

// find_cmd.c
void find_command_path(char *input, t_node *unit, int *cmd_is_found);
char *ft_strconcat(char *path, char *cmd);

// find_args.c
int count_args(t_node *cmd, char **result);
void find_args(t_node *cmd, char **result, int *i, int *j);

//find_flags.c
int		count_flags(char **result);
void 	find_flags(char *result, t_node *unit, int *i);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/17 16:41:01 by apple            ###   ########.fr       */
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
#include <sys/wait.h>
#include "../libft/libft.h"

#define PS1 "> "
#define B_IN 1
#define NON_B_IN 2
#define BOLD_BLUE "\033[1;34m"
#define ORANGE "\033[38;5;208m"
#define RESET "\033[0m"
#define PROMPT BOLD_BLUE "minishell" ORANGE "$ " RESET

typedef struct s_node t_node;

typedef struct	s_shell
{
	char	**env;
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
	int	cmd_type;
	int is_pipe;
	t_node *next;
}	t_node;


//typedef struct	s_cmd

//main.c
void	shell_loop(t_shell *shell);

//env.c
void	init_env(char **ev, t_shell *shell);
int		index_from_key(char *var_name, char **env_array);
char	*value_from_key(char *var_name, t_shell *shell);
int		count_vars(char **ev);
void	copy_vars(char **ev, char ***env_array);

//env2.c
int		change_env_value(char *var_name, char *new_value, t_shell *shell);
char	*key_from_index(int	pos, t_shell *shell);

//signal.c
void	activate_ctrlc(int sig);
void	deactivate_ctrlc(int sig);

//exec_utils.c
int	is_builtin(char *cmd);

//exec.c
void	execute_other(t_node *command);
void	execute_builtin(t_node *command);
char	**build_argv(t_node *node);

//BUILTINS
void	ft_pwd(t_node *command);
void	ft_env(t_node *command);
void	ft_cd(t_node *command);
void	ft_echo(t_node *command);
void	ft_export(t_node *command);

//ALINA
//prompt.c
int create_prompt(char *rl, t_shell *shell);

// parsing
char **split_args(char *str);
void read_the_input(char *rl, t_shell *shll);

//free
void free_arr(char **arr);
void free_node_arr(char **arr, int arr_length);
void free_linked_list(t_node *node);

// split the linked list
void add_cmds_flags_to_linked_list(char **result, t_node **unit);

// parse_input
// fill_unit_linked_list
t_node *add_unit_to_end(t_node **head);
t_node *create_unit();

//split_readline.c
char *extract_token(const char *str, int *i);
char *extract_token_v2(const char *str);
// find_cmd.c
int find_command_path(char *input, t_node *unit, int *cmd_is_found);

// find_args.c
int count_args(char **result, t_node *current_node);
void find_args(t_node *cmd, char **result, int *i, int *j);
int count_args_inside_loop(char **result, t_node *current_node, int *i);
char *retrieve_cmd_name(t_node *node);

//find_flags.c
int		count_flags(char **result);
void 	find_flags(char *result, t_node *unit, int *i);

// utils.c
int		is_valid_command(t_node *current_node, char *rl);
int		rl_is_space(char *rl);
int		is_operator(char *c);

// piping.c
void create_pipe(t_node *node);

// piping_utils.c
int find_list_len(t_node *node);

#endif

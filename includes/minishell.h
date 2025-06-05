/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/05 16:32:42 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define PS1 "> "
# define B_IN 1
# define NON_B_IN 2
# define PROMPT "\033[1;34mminishell\033[38;5;208m$ \033[0m"

typedef struct s_node	t_node;

typedef struct s_shell
{
	char	**env;
	t_node	*cmds;
	int		errcode;
}	t_shell;

typedef struct s_redir
{
	char *file_name;
	struct s_redir *next;
}	t_redir;

typedef struct s_node
{
	t_shell	*shell;
	char 	*cmd;
	char	*fcmd;	
	char 	**flags;
	char 	**args;
	char 	**vars;
	t_redir *redir_files;
	int 	stdin_redirect;
	int 	cmd_is_found;
	int 	flags_count;
	int 	args_count;
	int 	vars_count;
	int		cmd_type;
	int		is_pipe;
	t_node 	*next;
}	t_node;

//main.c
void	shell_loop(t_shell *shell);
void	print_node(t_node *command);

//env.c
void	init_env(char **ev, t_shell *shell);
int		index_from_key(char *var_name, char **env_array);
char	*value_from_key(char *var_name, t_shell *shell);
int		count_vars(char **ev);
void	copy_vars(char **ev, char ***env_array);

//env2.c
int		change_env_value(char *var_name, char *new_value, t_shell *shell);
char	*key_from_index(int pos, t_shell *shell);

//signal.c
void	activate_ctrlc(int sig);
void	deactivate_ctrlc(int sig);

//exec_utils.c
int		is_builtin(char *cmd);

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
void	ft_exit(t_node *command);
void	ft_unset(t_node *command);

//expand
void	process_exp(t_node *command);
char	*perfect(t_node *command, char **arr);

//builtins_utils.c
// char	**process_rl_line(t_node *command, char *rl_buffer);
void	process_str_exp(t_node *command, char **rl_buffer);

//ALINA
// parsing
char	**split_args(char *str);
void	read_the_input(char *rl, t_shell *shll);
char	*handle_quotes(char *str);

//free.c
void	free_arr(char **arr);
void	free_exit(t_shell *shell);
// void	free_node_arr(char **arr, int arr_length);
// void	free_linked_list(t_node *node);
void	iterate_free_nodes(t_node *head);
void	free_double_n(void **arr, int n);


// split the linked list
int		add_cmds_flags_to_linked_list(char **result, t_node **unit);

// parse_input
// fill_unit_linked_list
t_node	*add_unit_to_end(t_node **head);
t_node	*create_unit(void);

//split_readline.c
char	*extract_token(const char *str, int *i);
char	*extract_token_v2(const char *str);
void	trim_quotes_if_needed(char *token, int len);
void	trim_outer(char *str);
// find_cmd.c
int find_command_path(char *input, t_node *unit);

// find_args.c
int		count_args(char **result, t_node *current_node, int j_temp);
void	find_args(t_node *cmd, char **result, int *i, int *j);
int		count_args_inside_loop(char **result, t_node *current_node, int *i);
char	*retrieve_cmd_name(t_node *node);
int		alloc_mem_for_args_arr(t_node *current_node);

//find_flags.c
int		count_flags(char **result, int j);
// void 	find_flags(char *result, t_node *unit, int *i);
void	find_flags(char *result, t_node *current_node, int *i);
char	*ft_strdup2(const char *s1);

// find_vars.c
int count_variables(char **result, int *j);
int alloc_mem_for_vars_arr(t_node *current_node);
void find_vars(char *result, t_node *current_node, int *c);

// utils.c
int		is_valid_command(t_node *current_node, char *rl);
int		rl_is_space(char *rl);
int		is_operator(char *c);
int		condition_is_met(t_node *current_node, char *cmd_name, char **result, int j_temp);

// piping.c
void	create_pipe(t_node *node);

// redirection.c
int redirect_to_stdin(t_redir *node);
int redirect_to_stdout(t_redir *node); 

#endif

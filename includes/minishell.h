/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/13 15:03:55 by hceviz           ###   ########.fr       */
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
# define EXPERR "\e[0;31mminishell: export: `%s': not a valid identifier\n"

typedef struct s_node	t_node;

typedef struct s_shell
{
	char	**env;
	t_node	*cmds;
	int		errcode;
}	t_shell;

typedef struct s_redir_type
{
	int stdin_redir;
	int stdout_redir;
	int append_redir;
	int heredoc_redir;
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type *type;
	char *file_name;
	struct s_redir *next;
}	t_redir;

typedef struct s_node
{
	t_shell	*shell;
	char	*cmd;
	char	*fcmd;
	char	**flags;
	char	**args;
	t_redir *redir_files;
	int cmd_status;
	int cmd_is_found;
	int flags_count;
	int args_count;
	int vars_count;
	int	cmd_type;
	int is_pipe;
	t_node *next;
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

//exec.c
void	execute_other(t_node *command);
void	execute_builtin(t_node *command);
char	**build_argv(t_node *node);
void	handle_redir_heredoc_append(t_redir *redir);

//handlequotes.c
char 	*handle_quotesv2(char *str);

//BUILTINS
void	ft_pwd(t_node *command);
void	ft_env(t_node *command);
void	ft_cd(t_node *command);
void	ft_echo(t_node *command);
void	ft_export(t_node *command);
void	ft_exit(t_node *command);
void	ft_unset(t_node *command);

//expand
// void	process_exp(t_node *command);
char	*process_exp(char **result, t_node *unit);
char	*perfect(t_node *command, char *arr);
int		fake_perfect(t_node *command, char *arr);


//ALINA
// parse_input.c
char	**split_args(char *str);
void	read_the_input(char *rl, t_shell *shll);
int		check_for_redir_heredoc(t_node *current_node, char **result, int *j);

// parse_input_utils.c
void	go_to_execute(t_node *unit);
void	check_for_empty_line(char *rl);
int		is_input_redir(t_node *current_node, char **result, int *j);
int		is_output_redir(t_node *current_node, char **result, int *j);
int		is_heredoc_redir(t_node *current_node, char **result, int *j);
int		is_append_redir(t_node *current_node, char **result, int *j);

//free.c
void	free_arr(char **arr);
void	free_exit(t_shell *shell);
void	iterate_free_nodes(t_node *head);
void	free_double_n(void **arr, int n);


// split the linked list
int		add_cmds_flags_to_linked_list(char **result, t_node **unit);

// exec_utils.c
int		handle_stdin_redirection(t_redir *redir);
int		handle_stdout_redirection(t_redir *redir);
int		handle_heredoc_redirection(t_redir *redir);
int		handle_append_redirection(t_redir *redir);
int		is_builtin(char *cmd);

// fill_unit_linked_list.c
// void	add_new_file(t_redir **head, char *file_name);
t_redir *add_new_file(t_redir **head, char *file_name);
t_node	*add_unit_to_end(t_node **head);
t_node	*create_unit(void);

// split_readline_utils.c
void check_for_operator(char *token, char **result, int *count, int len);

// split_readline.c
// char	*extract_token(const char *str, int *i, char **result, int *count);
char	*extract_token(const char *str, int *i);
char	*extract_token_v2(const char *str);
void	trim_quotes_if_needed(char *token, int len);

// find_cmd.c
int		find_command_path(char *input, t_node *unit);

// find_args.c
int		count_args(char **result, t_node *current_node, int j_temp);
void	find_args(t_node *cmd, char **result, int *i, int *j);
char	*retrieve_cmd_name(t_node *node);
int		allocate_args_memory(t_node *current_node, char **result, int j_temp);
void	find_and_add_args(t_node *current_node, char **result, int *i, int *j);

//find_flags.c
int		count_flags(char **result, int j);
void	find_flags(char *result, t_node *current_node, int *i);
char	*ft_strdup2(const char *s1);

// find_vars.c
// int count_variables(char **result, int *j);
// int alloc_mem_for_vars_arr(t_node *current_node);
// void find_vars(char *result, t_node *current_node, int *c);

// utils.c
int		alloc_mem_for_flags_arr(t_node *current_node);
char	*handle_quotes(char *str);

// utils_2.c
char	**get_path(void);
int		handle_pipe(t_node **current_node, char **result, int i);
int		is_valid_command(t_node *current_node, char *rl);
void	handle_quotes_in_extract_token(const char *str, int *i, int *single_q, int *double_q);

// utils_3.c
int		rl_is_space(char *rl);
int		condition_is_met(t_node *current_node, char *cmd_name, char **result, int j_temp);
int		is_file_name(t_node *current_node, char *result);
int		alloc_mem_for_args_arr(t_node *current_node);

// piping.c
void	create_pipe(t_node *node);

// piping_utils.c
int		check_for_pipe(t_node **current_node, char **result, int *i, int *j);
void	handle_child(t_node *temp, int *pipe_fd, int prev_fd);
void	execute_depending_on_type(t_node *temp, char **argv, t_node *node);
void	handle_parent(t_node *temp, int prev_fd, int *pipe_fd);

// redirection.c
int		redirect_to_stdin(t_redir *node);
int		redirect_to_stdout(t_redir *node);
void	init_t_redir_type(t_redir *new_node);
int		heredoc(char *delimiter);
int		append(t_redir *node);

#endif

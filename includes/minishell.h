/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/07/04 13:16:19 by hceviz           ###   ########.fr       */
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
# include <sys/stat.h>
# include "../libft/libft.h"

# define PS1 "> "
# define B_IN 1
# define NON_B_IN 2
# define PROMPT "\033[1;34mminishell\033[38;5;208m$ \033[0m"
# define EXPERR "\e[0;31mminishell: export: '%s': not a valid identifier\n"

typedef struct s_node	t_node;

typedef struct s_quotes
{
	int	sq;
	int	dq;
}	t_quotes;

typedef struct s_shell
{
	char	**env;
	t_node	*cmds;
	int		exit_code;
}	t_shell;

typedef struct s_redir_type
{
	int	stdin_redir;
	int	stdout_redir;
	int	append_redir;
	int	heredoc_redir;
	int	has_out_redir;
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	*type;
	char			*file_name;
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	t_shell	*shell;
	char	*cmd;
	char	*fcmd;
	char	**flags;
	char	**args;
	t_redir	*redir_files;
	int		cmd_status;
	int		cmd_is_found;
	int		flags_count;
	int		args_count;
	int		vars_count;
	int		cmd_type;
	int		is_pipe;
	int		cmd_args_count;
	int		cmd_idx;
	int		n_flag;
	t_node	*next;
}	t_node;

typedef struct s_arg
{
	int		w_s;
	char	*str;
	char	*arr;
	t_shell	*shell;
}	t_arg;

// main.c
void	shell_loop(t_shell *shell);
void	print_node(t_node *command);

// env.c
void	init_env(char **ev, t_shell *shell);
int		index_from_key(char *var_name, char **env_array);
char	*value_from_key(char *var_name, t_shell *shell);
int		count_vars(char **ev);
void	copy_vars(char **ev, char ***env_array);

// env2.c
int		change_env_value(char *var_name, char *new_value, t_shell *shell);
char	*key_from_index(int pos, t_shell *shell);
void	add_key_val(t_shell *shell, char *key, char *val);

// signal.c
void	activate_ctrlc(int sig);
void	deactivate_ctrlc(int sig);

// exec.c
void	execute_other(char	**result, t_node *command);
void	execute_builtin(t_node *command, char **result);
char	**build_argv(t_node *node);

// BUILTINS
void	ft_pwd(t_node *command);
void	ft_env(t_node *command);
void	ft_cd(t_node *command);
void	ft_echo(t_node *command);
void	ft_export(t_node *command);
void	ft_exit(t_node *command, char **result);
void	ft_unset(t_node *command);

// ft_export_utils.c
int		value_syntax_ok(char *val);
void	create_and_set_val(t_shell *shell, char *key, char *val);
void	print_seperated_err(char *key, char *val, int mod);

// expander
char	*process_exp2(char ***result, t_node *unit, char **temp, int *count);
char	*process_exp(char **result, t_node *unit);
char	*iterate_and_replace(t_node *command, char *arr);

// expander_utils.c
void	delete_token_and_shift(char **result, int *count, int index);
int		is_alphanumeric(char a);
char	*replace_var(t_arg *arg, int pos, int len, int q);
int		q_ok(char *arr);

// parse_input.c
char	**split_args(char *str);
void	read_the_input(char *rl, t_shell *shll);
int		check_for_redir_heredoc(t_node *current_node, char **result, int *j);

// handle_quotes.c
char	*handle_quotesv2(char *str);

// parse_input_utils.c
void	go_to_execute(char **result, t_node *unit);
int		check_for_empty_line(char *rl);
int		is_input_redir(t_node *current_node, char **result, int *j);
int		is_output_redir(t_node *current_node, char **result, int *j);
int		is_heredoc_redir(t_node *current_node, char **result, int *j);
int		is_append_redir(t_node *current_node, char **result, int *j);

// free.c
void	iterate_free_nodes(t_node *head);
void	free_redir_list(t_redir *redir);
void	free_node_list(t_node *head);
void	free_linked_list(t_node *unit);

// free_utils.c
void	free_arr(char **arr);
void	free_exit(t_shell *shell);
void	free_shell(t_shell *shell);
void	safe_free(char **temp, char **temp2, int mod);

// split the linked list
int		add_cmds_flags_to_linked_list(char **result, t_node **unit);

// exec_utils.c
int		handle_stdin_redirection(t_redir *redir);
int		handle_stdout_redirection(t_redir *redir);
int		handle_heredoc_redirection(t_redir *redir);
int		handle_append_redirection(t_redir *redir);
int		is_builtin(char *cmd);

// exec_utils_1.c
int		handle_redir_heredoc_append(t_redir *redir);

// fill_unit_linked_list.c
t_redir	*add_new_file(t_redir **head, char *file_name);
t_node	*add_unit_to_end(t_node **head);
t_node	*create_unit(t_shell *shell);

// split_readline_utils.c
void	check_for_operator(char *token, char **result, int *count, int len);

// split_readline.c
char	*extract_token(char *str, int *i, char **result, int *count);
void	trim_quotes_if_needed(char *token, int len);
void	skip_whitespace(const char *str, int *i);

// find_cmd.c
int		find_command_path(char *input, t_node *unit);
void	set_error_status(char *input, t_node *unit);

// find_args.c
int		count_args(char **result, t_node *current_node, int k);
void	find_args(t_node *current_node, char **result, int i, int *j);
char	*retrieve_cmd_name(t_node *node);
int		allocate_args_memory(t_node *current_node, char **result, int j_temp);
void	find_and_add_args(t_node *current_node, char **result, int i, int *j);

// find_args_utils.c
int		count_echo_args(char **result, int k);
int		count_normal_args(char **result, t_node *current_node, int k);

// find_args_v2.c
int		count_args2(char **result, t_node *current_node, int j_temp);

//find_flags.c
int		count_flags(char **result, int j);
void	find_flags(char *result, t_node *current_node, int *i);
char	*ft_strdup2(const char *s1);

// utils.c
int		alloc_mem_for_flags_arr(t_node *current_node);
char	*handle_single_quotes(const char *str, int *i);
char	*handle_double_quotes(const char *str, int *i);
void	manage_parent_process(t_node *temp, int pipe_fd[2], int *prev_fd);
void	manage_child_process(t_node *temp, int pipe_fd[2],
			int prev_fd, char **result);

// utils_2.c
char	**get_path(void);
int		handle_pipe(t_node **current_node, char **result, int i, int cmd_idx);
void	handle_quotes_in_extract_token(const char *str, int *i,
			int *single_q, int *double_q);

// utils_3.c
int		rl_is_space(char *rl);
int		condition_is_met(t_node *current_node, char **result, int j_temp);
int		is_file_name(t_node *current_node, char *result);
int		alloc_mem_for_args_arr(t_node *current_node);
int		handle_pipe_and_move(t_node **current_node, char **result,
			int *i, int *j);

// utils_4.c
int		check_for_executable(t_node *unit, char *input);
void	split_token_on_operator(char *token, char **result, int *count);
void	extra_token_check(char *token, char **result, int *count, int len);

// utils_5.c
char	*extract_token_helper(char *token, int *count, char **result, int *i);
void	init_vars_in_func(int *single_q, int *double_q);
char	*subtract_token(char *token, char *str, int start, int len);
int		check_executable_errors(t_node *unit, char *input, struct stat *sb);

// utils_6.c
int		get_echo_args_start(char **result);
void	add_args_loop(char **result, t_node **unit, int i, int j);
int		parse_and_prepare(char *rl, t_shell *shll,
			char ***result, t_node **unit);

// utils_7.c
int		is_redir_or_pipe(char *token);
int		is_cmd_name(t_node *current_node, char **result, int j_temp);
int		is_non_flag_non_file_arg(t_node *current_node,
			char **result, int j_temp);

// piping.c
void	create_pipe(t_node *node, char **result);

// piping_utils.c
int		check_for_pipe(t_node **current_node, char **result, int *i, int *j);
void	handle_child(t_node *temp, int *pipe_fd, int prev_fd);
void	execute_depending_on_type(t_node *temp, char **argv, char **result);
void	handle_parent(t_node *temp, int prev_fd, int *pipe_fd);
void	exit_code(t_node *temp);

// redirection.c
int		redirect_to_stdin(t_redir *node);
int		redirect_to_stdout(t_redir *node);
void	init_t_redir_type(t_redir *new_node);
int		heredoc(char *delimiter);
int		append(t_redir *node);

#endif

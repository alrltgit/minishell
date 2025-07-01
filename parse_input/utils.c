/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:31:10 by alraltse          #+#    #+#             */
/*   Updated: 2025/07/01 18:46:40 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	alloc_mem_for_flags_arr(t_node *current_node)
{
	if (current_node->flags_count > 0)
	{
		current_node->flags = malloc(sizeof(char *)
				* (current_node->flags_count + 1));
		if (!current_node->flags)
			return (1);
	}
	else
	{
		current_node->flags = malloc(sizeof(char *));
		if (!current_node->flags)
			return (1);
		current_node->flags[0] = NULL;
	}
	return (0);
}

char	*handle_single_quotes(const char *str, int *i)
{
	char	*temp;

	temp = NULL;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			continue ;
		temp = update_str(temp, str[*i]);
	}
	return (temp);
}

char	*handle_double_quotes(const char *str, int *i)
{
	char	*temp;

	temp = NULL;
	while (str[++(*i)])
	{
		if (str[*i] == '"')
			continue ;
		temp = update_str(temp, str[*i]);
	}
	return (temp);
}

void	manage_child_process(t_node *temp, int pipe_fd[2],
	int prev_fd, char **result)
{
	char	**argv;

	argv = build_argv(temp);
	handle_child(temp, pipe_fd, prev_fd);
	execute_depending_on_type(temp, argv, result);
	free_arr(argv);
}

void	manage_parent_process(t_node *temp, int pipe_fd[2], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (temp->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		close(pipe_fd[0]);
}

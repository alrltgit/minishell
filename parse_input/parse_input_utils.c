/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:42:26 by apple             #+#    #+#             */
/*   Updated: 2025/06/18 16:50:57 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_empty_line(char *rl)
{
	if (rl_is_space(rl) == 1)
	{
		rl_on_new_line();
		rl_redisplay();
		return (1);
	}
	return (0);
}

int	is_input_redir(t_node *current_node, char **result, int *j)
{
	t_redir	*new_redir;

	if (result[*j + 1] == NULL)
		return (1);
	new_redir = add_new_file(&current_node->redir_files, result[*j + 1]);
	if (!new_redir)
		return (1);
	new_redir->type->stdin_redir = 1;
	(*j)++;
	return (0);
}

int	is_output_redir(t_node *current_node, char **result, int *j)
{
	t_redir	*new_redir;

	if (result[*j + 1] == NULL)
		return (1);
	new_redir = add_new_file(&current_node->redir_files, result[*j + 1]);
	if (!new_redir)
		return (1);
	new_redir->type->stdout_redir = 1;
	(*j)++;
	return (0);
}

int	is_heredoc_redir(t_node *current_node, char **result, int *j)
{
	t_redir	*new_redir;

	if (result[*j + 1] == NULL)
		return (1);
	new_redir = add_new_file(&current_node->redir_files, result[*j + 1]);
	if (!new_redir)
		return (1);
	new_redir->type->heredoc_redir = 1;
	(*j)++;
	return (0);
}

int	is_append_redir(t_node *current_node, char **result, int *j)
{
	t_redir	*new_redir;

	if (result[*j + 1] == NULL)
		return (1);
	new_redir = add_new_file(&current_node->redir_files, result[*j + 1]);
	if (!new_redir)
		return (1);
	new_redir->type->append_redir = 1;
	(*j)++;
	return (0);
}

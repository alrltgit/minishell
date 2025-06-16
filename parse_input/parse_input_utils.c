/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:42:26 by apple             #+#    #+#             */
/*   Updated: 2025/06/16 11:08:05 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_empty_line(char *rl)
{
	if (ft_strcmp(rl, "") == 0 || rl_is_space(rl) == 1)
	{
		// rl_replace_line("", 0);
		// rl_redisplay();
		// rl_on_new_line();
		return ;
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

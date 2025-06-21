/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:58:43 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/18 15:15:20 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_input_redirections(t_redir *redir)
{
	t_redir	*r;

	r = redir;
	while (r)
	{
		if (r->type->stdin_redir == 1)
		{
			if (handle_stdin_redirection(r) == 1)
				return (-1);
		}
		else if (r->type->heredoc_redir == 1)
		{
			if (handle_heredoc_redirection(r) == 1)
				return (-1);
		}
		r = r->next;
	}
	return (0);
}

int	handle_output_redirections(t_redir *redir)
{
	t_redir	*r;
	int		has_out_redir;

	r = redir;
	has_out_redir = 0;
	while (r)
	{
		if (r->type->stdout_redir || r->type->append_redir)
			has_out_redir = 1;
		if (r->type->stdout_redir == 1)
		{
			if (handle_stdout_redirection(r) == 1)
				return (-1);
		}
		else if (r->type->append_redir == 1)
		{
			if (handle_append_redirection(r) == 1)
				return (-1);
		}
		r = r->next;
	}
	return (has_out_redir);
}

int	handle_redir_heredoc_append(t_redir *redir)
{
	int	has_out_redir;

	has_out_redir = 0;
	if (handle_input_redirections(redir) == -1)
		return (-1);
	has_out_redir = handle_output_redirections(redir);
	return (has_out_redir);
}

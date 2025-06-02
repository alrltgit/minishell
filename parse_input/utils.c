/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:29:45 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/02 15:43:22 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
    is_valid_command problem:
    in case the command doesn't exist,
	the minishell prints the whole input line + :command not found;
    bash prints the current node + :the command not found. 
    Example: ls -l | -l:
    minishell: ls -l | -l: command not found;
    bash: -l: command not found;
*/

// int is_not_arg(t_node *current_node, char *str)
// {
// 	t_node *temp = current_node;

// 	while (temp)
// 	{
// 		if (temp->redir_files
// 			&& temp->redir_files->file_name)
// 		{
// 			if (ft_strcmp(temp->redir_files->file_name, str) == 0)
// 			{
// 				return (1);
// 			}
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }

int	condition_is_met(char *cmd_name, char **result, int j_temp)
{
	if (result[j_temp] == NULL)
		return (1);
	if (ft_strcmp(result[j_temp], "<") == 0 || ft_strcmp(result[j_temp], ">") == 0)
		return (1);
	if ((cmd_name == NULL && result[j_temp][0] != '-')
			|| (cmd_name != NULL && ft_strcmp(result[j_temp], cmd_name) != 0 && result[j_temp][0] != '-'))
	{
		return (0);
	}
	return (1);
}

int	rl_is_space(char *rl)
{
	char	*temp;

	temp = rl;
	while (*temp)
	{
		if (*temp != 32)
			return (1);
		temp++;
	}
	return (0);
}

int	is_valid_command(t_node *current_node, char *rl)
{
	if (current_node->cmd == NULL)
	{
		ft_putstr_fd(ft_strcat(rl, ": command not found\n"), 2);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:29:45 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/05 16:25:21 by alraltse         ###   ########.fr       */
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

int alloc_mem_for_flags_arr(t_node *current_node)
{
    if (current_node->flags_count > 0)
    {
        current_node->flags = malloc(sizeof(char *) * (current_node->flags_count + 1));
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

char	*handle_quotes(char *str)
{
	int	i;
	int	sq;
	int	dq;
	char	*temp;

	i = -1;
	sq = 0;
	dq = 0;
	temp = NULL;
	while (str[++i])
	{
		if (str[i] == '\'' && dq == 0)
		{
			sq = 1 - sq;
			while (str[++i])
			{
				if (str[i] == '\'')
					continue;
				temp = update_str(temp, str[i]);
			}
		}
		if (str[i] == '"' && sq == 0)
		{
			dq = 2 - dq;
			while (str[i++])
			{
				if (str[i] == '"')
					continue;
				temp = update_str(temp, str[i]);
			}
		}
		else
			temp = update_str(temp, str[i]);
	}
	return (temp);
}

int is_file_name(t_node *current_node, char *result)
{
	t_node *temp;

	temp = current_node;
	while (temp->redir_files)
	{
		// printf("temp->redir_files->file_name: %s\n", temp->redir_files->file_name);
		// printf("result: %s\n", result);
		if (ft_strcmp(temp->redir_files->file_name, result) == 0)
			return (1);
		temp->redir_files = temp->redir_files->next;
	}
	return (0);
}

int	condition_is_met(t_node *current_node, char *cmd_name, char **result, int j_temp)
{
	if (result[j_temp] == NULL)
		return (1);
	if (ft_strcmp(result[j_temp], "<") == 0 || ft_strcmp(result[j_temp], ">") == 0)
		return (1);
	if ((cmd_name == NULL && result[j_temp][0] != '-' && is_file_name(current_node, result[j_temp]) == 0
			&& is_file_name(current_node, result[j_temp]) == 0)
			|| (cmd_name != NULL && ft_strcmp(result[j_temp], cmd_name) != 0
			&& result[j_temp][0] != '-' && is_file_name(current_node, result[j_temp]) == 0))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:29:45 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/14 17:25:53 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
    is_valid_command problem:
    in case the command doesn't exist, the minishell prints the whole input line + :command not found;
    bash prints the current node + :the command not found. 
    Example: ls -l | -l:
    minishell: ls -l | -l: command not found;
    bash: -l: command not found;
*/

int	is_operator(char *c)
{
	if (ft_strcmp(c, "|") == 0 || ft_strcmp(c, "<") == 0
		|| ft_strcmp(c, ">") == 0 || ft_strcmp(c, ">>") == 0
		|| ft_strcmp(c, "<<") == 0)
		return (1);
	return (0);
}

int rl_is_space(char *rl)
{
    char *temp;

    temp = rl;
    while (*temp)
    {
        if (*temp != 32)
            return (1);
        temp++;
    }
    return (0);
}

int is_valid_command(t_node *current_node, char *rl)
{
    if (current_node->cmd == NULL)
    {
        ft_putstr_fd(ft_strcat(rl , ": command not found\n"), 2);
        return (1);
    }
    return (0);
}

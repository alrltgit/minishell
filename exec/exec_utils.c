/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:08:27 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/11 13:33:01 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/* void process_cmd(int cmd_type, t_node *node)
{
    if (cmd_type == B_IN)
    {
        // built_in;
    }
    else if (cmd_type == NON_B_IN)
    {
        // cmd_path;
    }
    else // 0
    {
        // cmd_not_found;
    }
} */

//int	is_valid_cmd()
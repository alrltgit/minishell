/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:16:52 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/01 11:43:53 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_only_number(char *fcmd)
{
	int	i;

	i = 5;
	if (fcmd[4] == '\0')
		return (1);
	while (fcmd[i])
	{
		if (!(fcmd[i] >= '0' && fcmd[i] <= '9'))
			return (0);
		++i;
	}
	return (1);
}

void	ft_exit(t_node *command, char **result)
{
	command->shell->exit_code = 0;
	ft_putstr_fd("exit\n", 2);
	if (!has_only_number(command->fcmd))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(command->fcmd + 4, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (command->args_count > 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return ;
	}
	if (result)
		free_double((void **)result);
	free_linked_list(command);
	exit(0);
}

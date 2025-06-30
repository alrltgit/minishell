/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:38:33 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/30 11:55:27 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_n_flag(t_node *command, int *i, int *w_n)
{
    int pos; 
	
	pos = *i;
    while (command->fcmd[pos] == ' ')
        pos++;
    while (command->fcmd[pos] == '-' && command->fcmd[pos + 1] == 'n')
    {
        int j = pos + 2;
        while (command->fcmd[j] == 'n')
            j++;

        if (command->fcmd[j] != ' ' && command->fcmd[j] != '\0')
            break;

        *w_n = 1;
        pos = j;
        while (command->fcmd[pos] == ' ')
            pos++;
    }

    *i = pos;
}

void	ft_echo(t_node *command)
{
	
	//(void)command;
	
	int	i;
	int	w_n;
	int	len;

	w_n = 0;
	i = -1;
	len = ft_strlen(command->fcmd);	
	i = 4;
	printf("fcmd before handle n flag -> %s\n", command->fcmd);
	if (command->fcmd[4] && command->fcmd[5] && command->fcmd[6]
		&& command->fcmd[4] == ' ' && command->fcmd[5] )
	handle_n_flag(command, &i, &w_n);
	printf("fcmd after handle n flag -> %s\n", command->fcmd);
	while (++i < len)
		write(1, &command->fcmd[i], 1);
	if (!w_n)
		printf("\n");
}

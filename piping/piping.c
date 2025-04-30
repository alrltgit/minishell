/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/04/30 14:31:32 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int piping(int argc, char **argv)
{
    t_cmd *c;
    
    c = malloc(sizeof(t_cmd));
    if (!c)
        return (0);
    c->argc_count = argc;
    if (is_command_valid(c, argv) == 0)
    {
        ft_printf("Command doesn't exist.\n");
        return (1);
    }
    ft_printf("The command exist.\n");
    return(0);
}
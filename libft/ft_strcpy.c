
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:52:05 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/12 13:53:26 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcpy(char *cmd_path, char *cmd, int j)
{
    int i;

    i = 0;
    while (cmd[i])
        cmd_path[j++] = cmd[i++];
    cmd_path[j] = '\0';
    return (cmd_path);
}

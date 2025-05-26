/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:29:23 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/22 18:29:56 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *cmd_path, char *cmd, int j)
{
	int	i;

	i = 0;
	while (cmd[i])
		cmd_path[j++] = cmd[i++];
	cmd_path[j] = '\0';
	return (cmd_path);
}

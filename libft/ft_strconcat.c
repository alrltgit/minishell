/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:34:42 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/22 18:35:15 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconcat(char *path, char *cmd)
{
	char	*cmd_path;
	int		i;
	int		j;

	cmd_path = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmd)) + 2);
	if (!cmd_path)
		return (NULL);
	i = 0;
	j = 0;
	while (path[i])
		cmd_path[j++] = path[i++];
	cmd_path[j++] = '/';
	return (ft_strcpy(cmd_path, cmd, j));
}

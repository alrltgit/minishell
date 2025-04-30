/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:48:26 by alraltse          #+#    #+#             */
/*   Updated: 2025/04/30 14:57:48 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	size_of_str(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != ' ' && str[len])
		len++;
	return (len);
}

static char	*ft_strcpy(char *cmd, char *str, int j)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i])
	{
		cmd[j] = str[i];
		j++;
		i++;
	}
	cmd[j] = '\0';
	return (cmd);
}

char	*ft_strconcat(char *path, char *str)
{
	int		i;
	int		j;
	char	*cmd;

	cmd = malloc(sizeof(char) * (ft_strlen(path) + size_of_str(str) + 2));
	if (!cmd)
	{
		perror("Allocation failed.\n");
		return (NULL);
	}
	j = 0;
	i = 0;
	while (i < path[i])
	{
		cmd[j] = path[i];
		i++;
		j++;
	}
    cmd[j++] = '/';
	return (ft_strcpy(cmd, str, j));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:29:45 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/06 14:43:22 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *ft_strcpy(char *cmd_path, char *cmd, int j)
{
    int i;

    i = 0;
    while (cmd[i])
        cmd_path[j++] = cmd[i++];
    cmd_path[j] = '\0';
    return (cmd_path);
}

char *ft_strconcat(char *path, char *cmd)
{
    char *cmd_path;
    int i;
    int j;
    
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



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:29:45 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/10 19:46:39 by apple            ###   ########.fr       */
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

int is_valid_command(t_node *current_node, char *rl)
{
    if (current_node->cmd == NULL)
    {
        ft_putstr_fd(ft_strcat(rl , ": command not found\n"), 2);
        return (1);
    }
    return (0);
}

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

char *ft_strcat(char *s1, char *s2)
{
    int i;
    int j;
    char *result;

    result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[i])
        result[j++] = s1[i++];
    i = 0;
    while (s2[i])
        result[j++] = s2[i++];
    result[j] = '\0';
    return (result);
}
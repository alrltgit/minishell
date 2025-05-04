/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/04 14:48:44 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **get_path()
{
    char *path;
    char **paths;

    path = getenv("PATH");
    paths = ft_split(path, ':');
    if (!paths)
        return (NULL);
    return (paths);
}

void find_command_path(t_lexer *lexers)
{
    char *temp_result;
    char **paths;
    t_lexer *temp;
    t_cmd *cmd;
    int i;
    
    cmd = malloc(sizeof(t_cmd));
    cmd->cmds = NULL;
    if (!cmd)
        return ;
    paths = get_path();
    if (!paths)
        return ;
    temp = lexers;
    while (temp)
    {
        i = 0;
        while (paths[i])
        {
            temp_result = ft_strconcat(paths[i], temp->data);
            if (access(temp_result, X_OK) == 0)
            {
                cmd->cmds = add_node_to_end(&cmd->cmds, temp_result);
                break ;
            }
            i++;
        }
        temp = temp->next;
    }
    // print cmds_linked_list
    while (cmd->cmds)
    {
        printf("cmd->lexer->data: %s\n", cmd->cmds->data);
        cmd->cmds = cmd->cmds->next;
    }
}
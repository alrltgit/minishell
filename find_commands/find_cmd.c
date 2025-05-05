/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:17 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/04 19:18:29 by apple            ###   ########.fr       */
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

void find_command_path(t_lexer *lexers, t_ast *ast)
{
    char *temp_result;
    char **paths;
    t_lexer *temp;
    int i;

    ast->cmds = NULL;
    if (!ast)
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
                ast->cmds = add_node_to_end(&ast->cmds, temp_result);
                break ;
            }
            i++;
        }
        temp = temp->next;
    }
    // print cmds_linked_list
    // while (cmd->cmds)
    // {
    //     printf("cmd->lexer->data: %s\n", cmd->cmds->data);
    //     cmd->cmds = cmd->cmds->next;
    // }
}
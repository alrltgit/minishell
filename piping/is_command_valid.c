/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:28:10 by alraltse          #+#    #+#             */
/*   Updated: 2025/04/30 14:55:01 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void add_cmds_to_arr(t_cmd *c)
{
    c->path = getenv("PATH");
    c->cmd_folders = ft_split(c->path, ':');
    //check paths
    // int i = 0;
    // while (c->cmd_folders[i])
    // {
    //     printf("%s\n", c->cmd_folders[i]);
    //     i++;       
    // }
}

int is_command_valid(t_cmd *c, char **argv)
{
    int idx;
    int i;
    int flag;
    char *temp_result;
    // (void)argv;
    add_cmds_to_arr(c);
    flag = 0;
    i = 1;
    // ft_printf("%d\n", c->argc_count);
    while (i < c->argc_count)
    {
        idx = 0;
        while (c->cmd_folders[idx])
        {
            // printf("%s\n", c->cmd_folders[idx]);
            // printf("%s\n", argv[i]);
            temp_result = ft_strconcat(c, c->cmd_folders[idx], argv[i]);
            c->cmds[i] = ft_strdup(temp_result);
            printf("c->cmds[i]: %s\n", c->cmds[i]);
            // if (access(c->cmds[i], X_OK) == 0)
            // {
            //     flag = 1;
            //     free(temp_result);
            //     return (flag);
            // }
            idx++;
            free(c->cmds[i]);
            free(temp_result);
        }
        i++;
    }
    return (flag);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:45:24 by alraltse          #+#    #+#             */
/*   Updated: 2025/04/30 14:38:24 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_cmd
{
    char **cmd_folders;
    int paths_count;
    char *path;
    int argc_count;
    char **cmds;
}       t_cmd;

// piping
int is_command_valid(t_cmd *c, char **argv);
int piping(int argc, char **argv);
char	*ft_strconcat(t_cmd *c, char *path, char *str);

#endif
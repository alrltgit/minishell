/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:43:35 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/01 15:12:39 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int redirect_to_stdin(t_redir *node) // "<" - redirects to STDIN from file
{
    int fd;

    // printf("node->file_name: %s\n", node->file_name);
    fd = open(node->file_name, O_RDONLY);
    if (fd < 0)
    {
        printf("%s: No such file or directory.\n", node->file_name);
        return (1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("Failed to redirect stdin\n");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return (0);
}

int redirect_to_stdout(t_redir *node) // ">" - redirects to STDOUT from file
{
    int fd;

    fd = open(node->file_name, O_RDONLY | O_WRONLY | O_TRUNC);
    if (fd < 0)
    {
        printf("%s: No such file or directory.\n", node->file_name);
        return (1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Failed to redirect stdout\n");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return (0);
}

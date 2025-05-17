/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:38:42 by apple             #+#    #+#             */
/*   Updated: 2025/05/17 21:41:13 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void create_pipe(t_node *node)
{
    t_node *temp = node;
    int prev_fd;
    int pipe_fd[2];
    pid_t pid;
    char **argv;

    prev_fd = -1;
    while (temp)
    {
        if (temp->next)
            pipe(pipe_fd);
        pid = fork();
        if (pid == 0)
        {
            // Child process
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (temp->next != NULL)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            argv = build_argv(temp);
            execve(temp->cmd, argv, temp->shell->env);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (temp->next)
        {
            close(pipe_fd[1]);         // Parent doesn't write
            prev_fd = pipe_fd[0]; // Save read end for next loop
        }
        while (wait(NULL) > 0);
        temp = temp->next;
    }
}
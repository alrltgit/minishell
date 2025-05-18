/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:38:42 by apple             #+#    #+#             */
/*   Updated: 2025/05/18 12:36:00 by apple            ###   ########.fr       */
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
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe failed");
            return;
        }
        argv = build_argv(temp);
        pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            free_arr(argv);
            return;
        }
        if (pid == 0)
        {
            fprintf(stderr, "Child process: executing command '%s'\n", temp->cmd);
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
            execve(temp->cmd, argv, temp->shell->env);
            perror("execve failed");
            free_arr(argv);
            exit(EXIT_FAILURE);
        }
        else
        {
            fprintf(stderr, "Parent process: handling command '%s'\n", temp->cmd);
            if (prev_fd != -1)
                close(prev_fd);
            if (temp->next)
            {
                close(pipe_fd[1]);
                prev_fd = pipe_fd[0];
            }
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            free_arr(argv);
            temp = temp->next;
        }
    }
    while (wait(NULL) > 0);
}
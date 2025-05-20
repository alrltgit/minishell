/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:38:42 by apple             #+#    #+#             */
/*   Updated: 2025/05/20 14:46:46 by alraltse         ###   ########.fr       */
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

    // char *const *envp = NULL;
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
            // fprintf(stderr, "Child process: executing command '%s'\n", temp->cmd);
            if (temp == node && temp->stdin_redirect == 1)
            {
                if (redirect_to_stdin(temp) == 1)
                    return ;
            }
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
            if (temp->cmd_type == B_IN)
            {
                execute_builtin(temp);
                exit(EXIT_SUCCESS);
            }
            else
            {
                execve(temp->cmd, argv, node->shell->env);
                perror("execve failed");
                free_arr(argv);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (prev_fd != -1)
                close(prev_fd);
            if (temp->next)
            {
                close(pipe_fd[1]);
                prev_fd = pipe_fd[0];
            }
            else
                close(pipe_fd[0]);
            temp = temp->next;
        }
    }
    while (wait(NULL) > 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:43:35 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/30 21:53:13 by apple            ###   ########.fr       */
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

void heredoc(t_node *current_node, char *delimiter)
{
    char *line;
    int fd_temp;
    pid_t pid;
    int status;

    fd_temp = open(current_node->redir_files->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_temp < 0)
    {
        printf("fd_temp didn't open\n");
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        while (1)
        {
            line = readline("> ");
            if (!line || ft_strcmp(line, delimiter) == 0)
                break ;
            write(fd_temp, line, ft_strlen(line));
            write(fd_temp, "\n", 1);
            free(line);
        }
        free(line);
        close(fd_temp);
        exit(0);
    }
    else if (pid > 0)
    {
        signal(SIGINT, SIG_IGN);
        waitpid(pid, &status, 0);
        close(fd_temp);
        if (WIFSIGNALED(status))
            return ;
    }
    else
    {
        perror("fork failed");
        return ;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:38:42 by apple             #+#    #+#             */
/*   Updated: 2025/06/09 13:44:20 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_for_pipe(t_node **current_node, t_node **unit, char **result, int *i, int *j, int *c)
{
    int j_temp;

    if (ft_strcmp(result[*j], "|") == 0)
    {
        (*current_node)->is_pipe = 1;
        *current_node = add_unit_to_end(unit);
        if (!*current_node)
            return (1);
        j_temp = *j + 1;
        if (!result[j_temp])
            return (1);
        (*current_node)->flags_count = count_flags(result, j_temp);
        if (alloc_mem_for_flags_arr(*current_node) == 1)
            return (1);
        *i = 0;
        *c = 0;
        (*current_node)->cmd_is_found = 0;
        (*j)++;
    }
    return (0);
}

void	create_pipe(t_node *node)
{
	t_node	*temp;
	int		prev_fd;
	int		pipe_fd[2];
    int     fd;
	pid_t	pid;
	char	**argv;
    t_redir *redir;

    temp = node;
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
            return ;
        }
        if (pid == 0)
        {
            redir = temp->redir_files;
            while (redir)
            {
                if (redir->type->stdin_redir == 1)
                {
                    if (redirect_to_stdin(redir) == 1)
                        exit(1);
                }
                else if (redir->type->stdout_redir == 1)
                {
                    if (redirect_to_stdout(redir) == 1)
                        exit(1);
                }
                else if (redir->type->heredoc_redir == 1)
                {
                    if (heredoc(redir->file_name) == 1)
                        exit(1);
                    fd = open("fd_temp", O_RDONLY);
                    if (fd < 0)
                    {
                        perror("open fd_temp failed");
                        exit(1);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }
                else if (redir->type->append_redir == 1)
                {
                    if (append(redir) == 1)
                        exit(1);
                }
                redir = redir->next;
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
    unlink("fd_temp");
}

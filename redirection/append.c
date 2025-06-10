/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:43:58 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/10 10:32:08 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append(t_redir *node)
{
	int	fd;

	fd = open(node->file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory.\n", node->file_name);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Failed to append\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:47:58 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/14 11:13:53 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**build_argv(t_node *node)
{
	int i;
	int j;
	char	**argv;
	int		total_count;

	total_count = 1 + node->flags_count + node->args_count;
	argv = malloc(sizeof(char *) * (total_count + 1));
	if (!argv)
		return (NULL);

	i = 0;
	argv[i++] = ft_strdup(retrieve_cmd_name(node));
	j = 0;
	while (j < node->flags_count)
		argv[i++] = ft_strdup(node->flags[j++]);
	j = 0;
	while (j < node->args_count)
		argv[i++] = ft_strdup(node->args[j++]);
	argv[i] = NULL;
	return (argv);
}
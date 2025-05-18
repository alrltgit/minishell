/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:47:58 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/18 17:23:32 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup2(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1)
	{
		return (NULL);
	}
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**build_argv(t_node *node)
{
	int i;
	int j;
	char **argv;
	int total_count;

	total_count = 1 + node->flags_count + node->args_count;
	argv = malloc(sizeof(char *) * (total_count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	argv[i] = ft_strdup2(retrieve_cmd_name(node));
	if (argv[i] == NULL)
	{
		printf("argv[i] = NULL\n");
		return (NULL);
	}
	i++;
	if (node->flags)
	{
		j = 0;
		while (j < node->flags_count)
		{
			argv[i] = ft_strdup2(node->flags[j]);
			if (argv[i] == NULL)
			{
				return (NULL);
			}
			i++;
			j++;
		}
	}
	j = 0;
	if (node->args)
	{
		while (j < node->args_count)
		{
			argv[i] = ft_strdup2(node->args[j]);
			if (argv[i] == NULL)
			{
				return (NULL);
			}
			i++;
			j++;
		}
	}
	argv[i] = NULL;
	return (argv);
}
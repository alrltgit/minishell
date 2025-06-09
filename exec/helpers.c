/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:47:58 by alraltse          #+#    #+#             */
/*   Updated: 2025/06/09 17:00:13 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup2(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
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

void	include_flags(t_node *node, char **argv, int *i)
{
	int	j;

	j = 0;
	if (node->flags_count > 0)
	{
		j = 0;
		while (j < node->flags_count)
		{
			argv[*i] = ft_strdup2(node->flags[j]);
			if (argv[*i] == NULL)
				return ;
			(*i)++;
			j++;
		}
	}
}

void	include_args(t_node *node, char **argv, int *i)
{
	int	j;

	j = 0;
	if (node->args)
	{
		while (j < node->args_count)
		{
			argv[*i] = ft_strdup2(node->args[j]);
			if (argv[*i] == NULL)
				return ;
			(*i)++;
			j++;
		}
	}
}

char	**build_argv(t_node *node)
{
	int		i;
	int		total_count;
	char	**argv;

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
	include_flags(node, argv, &i);
	include_args(node, argv, &i);
	argv[i] = NULL;
	return (argv);
}

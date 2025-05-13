/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:47:58 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/13 14:32:37 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *build_args_string(t_node *node)
{
	char	*argv;
	int		args_size;
	char 	*args;

	args_size = count_arr_size(node->args, node->args_count);
	argv = malloc(sizeof(char) * (args_size + 1));
	if (!argv)
		return (NULL);
	args = join_strings_with_spaces(args_size, node->args_count, node->args);
	argv = ft_strdup(args);
	free(args);
	return (argv);
}

char *build_flags_string(t_node *node)
{
	char	*argv;
	int		flags_size;
	char	*flags;

	flags_size = count_arr_size(node->flags, node->flags_count);
	argv = malloc(sizeof(char) * (flags_size + 1));
	if (!argv)
		return (NULL);
	flags = join_strings_with_spaces(flags_size, node->flags_count, node->flags);
	argv = ft_strdup(flags);
	free(flags);
	return (argv);
}

char *build_args_flags_string(t_node *node)
{
	int flags_size;
	int args_size;
	char *argv;
	char *flags;
	char *args;
	
	flags_size = count_arr_size(node->flags, node->flags_count);
	args_size = count_arr_size(node->args, node->args_count);
	argv = malloc(sizeof(char) * (flags_size + args_size + 1));
	if (!argv)
		return (NULL);
	flags = join_strings_with_spaces(flags_size, node->flags_count, node->flags);
	args = join_strings_with_spaces(args_size, node->args_count, node->args);
	argv[0] = '\0';
	argv = ft_strcat(argv, flags);
	argv = ft_strcat(argv, " ");
	argv = ft_strcat(argv, args);
	free(flags);
	free(args);
	return (argv);
}

char	**build_argv(t_node *node)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(node->cmd);
	if (!argv[0])
		return (NULL);
	if (node->flags_count == 0 && node->args_count == 0)
		argv[1] = NULL;
	else if (node->flags_count == 0)
	{
		argv[1] = build_args_string(node);
	}
	else if (node->args_count == 0)
	{
		argv[1] = build_flags_string(node);
	}
	else
	{
		argv[1] = build_args_flags_string(node);
	}
	argv[2] = NULL;
	return (argv);
}
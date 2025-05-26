/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:36:40 by apple             #+#    #+#             */
/*   Updated: 2025/05/26 17:03:39 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_variables(char **result, int *j)
{
	int		vars_count;
    int     i;

    i = *j;
    vars_count = 0;
	while (result[i])
	{
		if (is_operator(result[i]) == 0)
			break ;	
		if (result[i][0] == '$')
			vars_count++;
		i++;
	}
	return (vars_count);
}

int alloc_mem_for_vars_arr(t_node *current_node)
{
    if (current_node->vars_count > 0)
    {
        current_node->vars = malloc(sizeof(char *) * (current_node->vars_count));
        if (!current_node->vars)
            return (1);
    }
    else
    {
        current_node->vars = malloc(sizeof(char *));
        if (!current_node->vars)
            return (1);
        current_node->vars[0] = NULL;
    }
    return (0);
}

// int find_vars(char *result, t_node *current_node, int *i)
// {
//     int     i;

//     i = *j;
//     vars_count = 0;
// 	while (result[i])
// 	{
// 		if (is_operator(result[i]) == 0)
// 			break ;	
// 		if (result[i][0] == '$')
// 			vars_count++;
// 		i++;
// 	}
// }
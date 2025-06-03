/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:36:40 by apple             #+#    #+#             */
/*   Updated: 2025/06/03 11:13:02 by hceviz           ###   ########.fr       */
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
		if (ft_strcmp(result[i], "|") == 0)
		{
			break ;
		}
		if (result[i][0] == '$')
		{
			vars_count++;
		}
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

void find_vars(char *result, t_node *current_node, int *c)
{
	if (result[0] == '$')
	{
		// printf("IN\n");
		current_node->vars[*c] = ft_strdup2(result);
		current_node->fcmd = ft_strjoin_free(current_node->fcmd, result); //check
		// printf("current_node->vars[*c] %s\n", current_node->vars[*c]);
		(*c)++;	
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:35:45 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/01 14:25:39 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
	HANDLE

	export abc
	export abc=
	export abc = 5
	export =
	export abc= 5
	export abc =5
	export abc def g=2
	export abc def g =2
	export abc def g= 2
	export abc=5 def=3

	export qweqwe=5 | echo adasdad | export xcvbxcv=3
*/
int	has_equal_sign(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}
void	ft_export(t_node *command)
{
	char	**split;
	int		i;
	int		j;
	char	**res;

	process_rl_line(command, &rl_line_buffer);
	split = split_args(rl_line_buffer, 0);
	i = -1;
	while (split[++i])
	{
		if (ft_strcmp(split[i], "export") == 0)
		{
			j = 0;
			res[j] = ft_strdup(split[i]);
			while (!is_operator(split[++i]))
				res[++j] = ft_strdup(split[i]);
		}

	}
	print_node(command);
	//int	i;

	/* i = -1;
	if ()
	while */

}
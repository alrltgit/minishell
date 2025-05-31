/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:43:25 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/31 12:51:52 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* char	*process_rl_line(t_node *command, char *rl_buffer)
{
	char	**res;
	char	*temp;
	int		len;
	int		count;

	len = -1;
	res = split_args(rl_buffer);
	while (res[++len])
		;
	count = -1;
	temp = NULL;
	while (++count < len)
	{
		temp = ft_strdup(res[count]);
		free(res[count]);
		res[count] = ft_strdup(handle_quotes(perfect(command, &temp)));
		//trim_outer(input_split[count]);
	}
	return (res);
} */

void	process_rl_line(t_node *command, char **rl_buffer)
{
	char	*temp;
	int		len;

	len = -1;
	temp = NULL;
	temp = ft_strdup(handle_quotes(perfect(command, rl_buffer)));
	free(*rl_buffer);
	*rl_buffer = ft_strdup(temp);
	free(temp);
}
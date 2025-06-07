/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:43:25 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/07 11:06:41 by hceviz           ###   ########.fr       */
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

void	process_str_exp(t_node *command, char **rl_buffer)
{
	char	*temp;
	// int		len;

	// len = -1;
	temp = NULL;
	temp = ft_strdup(handle_quotes(perfect(command, rl_buffer)));
	printf("PROCESSED TEMP RL-> %s\n", temp);
	free(*rl_buffer);
	*rl_buffer = ft_strdup(temp);
	free(temp);
	temp = NULL;
}

/* void	process_str_exp(t_node *command, char **rl_buffer)
{
	char	*processed;
	char	*quoted;

	quoted = handle_quotes(perfect(command, rl_buffer));
	if (!quoted)
		return;
	printf("Before strdup: [%s] (len = %zu)\n", quoted, strlen(quoted));
	
	processed = ft_strdup(quoted);
	if (!processed)
		return;

	free(*rl_buffer);
	*rl_buffer = processed;
} */

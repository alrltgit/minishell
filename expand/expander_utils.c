/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:37:47 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/03 15:25:56 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	q_ok(char *arr)
{
	int	i;
	int	in_sq;
	int	in_dq;

	i = 0;
	in_dq = 0;
	in_sq = 0;
	while (arr[i])
	{
		if (arr[i] == '\'' && in_dq == 0)
			in_sq = !in_sq;
		else if (arr[i] == '"' && in_sq == 0)
			in_dq = !in_dq;
		i++;
	}
	if (in_sq || in_dq)
		return (0);
	return (1);
}

void	delete_token_and_shift(char **result, int *count, int index)
{
	int	j;

	free(result[index]);
	j = index;
	while (result[j + 1])
	{
		result[j] = result[j + 1];
		j++;
	}
	result[j] = NULL;
	(*count)--;
}

int	is_alphanumeric(char a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')
		|| (a >= '0' && a <= '9') || a == '_' || a == '?')
		return (1);
	return (0);
}

//var arr
//str str
char	*replace_var(t_arg *arg, int pos, int len, int q)
{
	char	*tmp;
	int		j;
	char	*tmp2;

	tmp = NULL;
	j = -1;
	if (q == 1)
		tmp = ft_substr(arg->arr, pos + 1, len - 1);
	else if (arg->arr[pos] == '?')
		tmp = ft_itoa(arg->shell->exit_code);
	else
	{
		tmp2 = ft_substr(arg->arr, pos, len);
		tmp = ft_strdup(value_from_key(tmp2, arg->shell));
		free(tmp2);
		if (ft_strcmp(tmp, " ") == 0)
		{
			free(tmp);
			return (ft_strdup(" "));
		}
	}
	while (tmp && tmp[++j])
		arg->str = update_str(arg->str, tmp[j]);
	free(tmp);
	return (arg->str);
}

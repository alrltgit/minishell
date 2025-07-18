/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:28:07 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/04 13:27:19 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_dollar(t_arg *arg, int *i, int qte)
{
	int		j;
	int		len;

	j = *i;
	len = 0;
	if (arg->arr[*i + 1] == '?')
	{
		arg->str = replace_var(arg, *i + 1, 1, qte);
		*i += 1;
		return (arg->str);
	}
	while (is_alphanumeric(arg->arr[++j]))
		++len;
	arg->str = replace_var(arg, *i + 1, len, qte);
	*i += len;
	return (arg->str);
}

char	*iterate_and_replace(t_node *command, char *arr)
{
	int		in_sq;
	int		in_dq;
	int		i;
	t_arg	args;

	in_sq = 0;
	in_dq = 0;
	i = -1;
	args.str = NULL;
	args.arr = arr;
	args.shell = command->shell;
	while (arr[++i])
	{
		(void)((arr[i] == '\'') && (!in_dq) && (in_sq = 1 - in_sq));
		(void)((arr[i] == '"') && (!in_sq) && (in_dq = 2 - in_dq));
		if (arr[i] == '$' && !in_sq && is_alphanumeric(arr[i + 1]))
		{
			args.str = handle_dollar(&args, &i, in_sq + in_dq);
			continue ;
		}
		else
			args.str = update_str(args.str, arr[i]);
	}
	return (args.str);
}

char	*process_exp3(char ***result, t_node *unit, char **temp, char **temp2)
{
	int		i;
	char	*tmp;

	i = 0;
	*temp = NULL;
	*temp2 = NULL;
	while ((*result)[i] && (*result)[++i])
	{
		if (!q_ok((*result)[i]))
			return ((*result)[i]);
		*temp = ft_strdup((*result)[i]);
		*temp2 = iterate_and_replace(unit, *temp);
		if ((*temp2) == NULL || (*temp2)[0] == '\0')
		{
			free((*result)[i]);
			(*result)[i] = ft_strdup("");
			safe_free(temp, temp2, 3);
			continue ;
		}
		free((*result)[i]);
		tmp = handle_quotesv2(*temp2);
		safe_free(temp, temp2, 3);
		(*result)[i] = tmp;
	}
	return (NULL);
}

char	*process_exp2(char ***res, t_node *unit, char **temp, int *count)
{
	*temp = NULL;
	if ((*res)[0])
	{
		if (!q_ok((*res)[0]) || ((((*res)[0][0] == '"' && (*res)[0][1] == '"')
			|| ((*res)[0][0] == '\'' && (*res)[0][1] == '\'')) && !(*res)[2]))
			return ((*res)[0]);
		*temp = iterate_and_replace(unit, (*res)[0]);
		if ((*temp) == NULL || (*temp)[0] == '\0')
		{
			delete_token_and_shift(*res, count, 0);
			safe_free(temp, NULL, 1);
			return (process_exp(*res, unit));
		}
		else
		{
			free((*res)[0]);
			(*res)[0] = handle_quotesv2(*temp);
		}
	}
	safe_free(temp, NULL, 1);
	return (NULL);
}

char	*process_exp(char **result, t_node *unit)
{
	char	*temp;
	char	*temp2;
	char	*res;
	int		count;

	count = -1;
	while (result[++count])
		;
	res = process_exp2(&result, unit, &temp, &count);
	if (res != NULL)
		return (res);
	free(res);
	res = process_exp3(&result, unit, &temp, &temp2);
	if (res != NULL)
		return (res);
	return (NULL);
}

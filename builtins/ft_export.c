/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:48 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/04 13:31:40 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_alphanumeric_export(char *key)
{
	int	i;

	i = -1;
	while (key[++i])
	{
		if (!(key[i] >= 'a' && key[i] <= 'z')
			&& !(key[i] >= 'A' && key[i] <= 'Z')
			&& !(key[i] >= '0' && key[i] <= '9')
			&& key[i] != '=')
			return (0);
	}
	return (1);
}

int	check_print_error(char *key, char *val, int w_space)
{
	if (!is_alphanumeric_export(key))
	{
		if (w_space)
			print_seperated_err(key, val, 1);
		else
			print_seperated_err(key, val, 2);
	}
	else
	{
		if (w_space)
			print_seperated_err(key, val, 4);
		else
		{
			if (!value_syntax_ok(val))
				print_seperated_err(key, val, 2);
			else
				return (1);
		}
	}
	return (0);
}

char	**check2(t_arg *arg, int b_l, char **tmp)
{
	char	**arr;

	while (arg->arr[--b_l] && arg->arr[b_l] != ' ')
		*tmp = update_str(*tmp, arg->arr[b_l]);
	free(arg->arr);
	b_l = ft_strlen(*tmp) + 1;
	arg->arr = NULL;
	while (b_l)
		arg->arr = update_str(arg->arr, (*tmp)[--b_l]);
	free(*tmp);
	if (!check_print_error(arg->arr, arg->str, arg->w_s))
	{
		arg->shell->exit_code = 1;
		free(arg->arr);
		free(arg->str);
		return (NULL);
	}
	arr = malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup(arg->arr);
	arr[1] = ft_strdup(arg->str);
	free(arg->arr);
	free(arg->str);
	return (arr);
}

char	**check_invalid_identifier1(char *str, t_node *node)
{
	t_arg	arg;
	char	*temp;
	int		i;
	int		b_len;

	node->shell->exit_code = 0;
	arg.shell = node->shell;
	arg.w_s = 0;
	arg.str = ft_strchr(str, '=');
	b_len = ft_strlen(str) - ft_strlen(arg.str);
	arg.arr = ft_substr(str, 0, b_len);
	i = -1;
	temp = NULL;
	while (arg.str[++i] && arg.str[i] != ' ')
		temp = update_str(temp, arg.str[i]);
	arg.str = ft_strdup(temp);
	free(temp);
	temp = NULL;
	if (arg.arr[b_len - 1] && arg.arr[b_len - 1] == ' ')
	{
		arg.w_s = 1;
		--b_len;
	}
	return (check2(&arg, b_len, &temp));
}

void	ft_export(t_node *command)
{
	char	**split;
	int		index;
	int		count;

	if (ft_strcmp(command->fcmd, "export") == 0)
	{
		index = -1;
		count = count_vars(command->shell->env);
		while (++index < count)
			printf("declare -x %s\n", command->shell->env[index]);
		return ;
	}
	split = check_invalid_identifier1(command->fcmd, command);
	if (!split)
		return ;
	index = index_from_key(split[0], command->shell->env);
	if (index == -1)
		create_and_set_val(command->shell, split[0], split[1]);
	else
		change_env_value(split[0], split[1] + 1, command->shell);
	free(split[0]);
	free(split[1]);
	free(split);
}

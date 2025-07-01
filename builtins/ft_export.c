/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:48 by hceviz            #+#    #+#             */
/*   Updated: 2025/07/01 19:13:13 by apple            ###   ########.fr       */
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

char	**check2(t_node *n, int b_l, char **tmp, char *bf, char *af, int w_s)
{
	char	**arr;

	while (bf[--b_l] && bf[b_l] != ' ')
		*tmp = update_str(*tmp, bf[b_l]);
	free(bf);
	b_l = ft_strlen(*tmp) + 1;
	bf = NULL;
	while (b_l)
		bf = update_str(bf, (*tmp)[--b_l]);
	free(*tmp);
	if (!check_print_error(bf, af, w_s))
	{
		n->shell->exit_code = 1;
		free(bf);
		free(af);
		return (NULL);
	}
	arr = malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup(bf);
	arr[1] = ft_strdup(af);
	free(bf);
	free(af);
	return (arr);
}

/*
	if there is invalid identifier for export
	return the array of invalid identifiers,
	else return NULL
*/
// export abc def kggjdfg should do nothing
char	**check_invalid_identifier1(char *str, t_node *node)
{
	char	*before;
	char	*after;
	char	*temp;
	int		i;
	int		b_len;
	int		key_w_skip;

	node->shell->exit_code = 0;
	key_w_skip = 0;
	after = ft_strchr(str, '=');
	b_len = ft_strlen(str) - ft_strlen(after);
	before = ft_substr(str, 0, b_len);
	i = -1;
	temp = NULL;
	while (after[++i] && after[i] != ' ')
		temp = update_str(temp, after[i]);
	after = ft_strdup(temp);
	free(temp);
	temp = NULL;
	if (before[b_len - 1] && before[b_len - 1] == ' ')
	{
		key_w_skip = 1;
		--b_len;
	}
	return (check2(node, b_len, &temp, before, after, key_w_skip));
}

//export abc =5

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

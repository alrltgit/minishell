/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:48 by hceviz            #+#    #+#             */
/*   Updated: 2025/06/05 16:51:44 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_alphanumeric(char *key)
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

/* char	*process_value(char	*value)
{
	int		count;
	char	*trimmed;

	if (value[0] == ' ')
		return (" ");
	trimmed = extract_token_v2(value);
	if (ft_strcmp(value, trimmed) != 0)
		return (trimmed);
	else
	{
		count = -1;
		while (value[++count] && value[count] != ' ')
			;
		return (ft_substr(value, 0, count));
	}
} */
/*
	if there is space after first = sign
	set empty line to value
*/

void	create_and_set_val(t_shell *shell, char *key, char *val)
{
	int		count;
	char	**new_env;

	count = count_vars(shell->env);
	new_env = malloc((count + 2) * sizeof(char *));
	if (!new_env)
		return ;
	copy_vars(shell->env, &new_env);
	new_env[count] = ft_strjoin(key, val);
	new_env[count + 1] = NULL;
	init_env(new_env, shell);
	free_double((void **)new_env);
}

int	check_print_error(char *key, char *val, int w_space)
{
	if (!is_alphanumeric(key))
	{
		if (w_space)
		{
			printf("\e[0;31mminishell: export11: `%s': not a valid identifier\n", key);
			printf("\e[0;31mminishell: export111: `%s': not a valid identifier\n", val);
		}
		else
			printf("\e[0;31mminishell: export: `%s': not a valid identifier\n", ft_strcat(key, val));
	}
	else
	{
		if (w_space)
			printf("\e[0;31mminishell: export: `%s': not a valid identifier\n", val);
		else
		{
			if (!is_alphanumeric(val))
				printf("\e[0;31mminishell: export: `%s': not a valid identifier\n", val);
			else
				return (1);
		}
	}
	return (0);
}

/*
	if there is invalid identifier for export
	return the array of invalid identifiers,
	else return NULL
*/
// export abc def kggjdfg should do nothing
char	**check_invalid_identifier(char *str)
{
	char	*before;
	char	*after;
	char	*temp;
	char	**arr;
	int		i;
	int		b_len;
	int		key_w_skip;

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
	i = -1;
	if (before[b_len - 1] && before[b_len - 1] == ' ')
	{
		key_w_skip = 1;
		--b_len;
	}
	while (before[--b_len] != ' ')
		temp = update_str(temp, before[b_len]);
	free(before);
	b_len = ft_strlen(temp) + 1;
	before = NULL;
	while (b_len)
		before = update_str(before, temp[--b_len]);
	free(temp);
	printf("BEFORE DEBUG -> %s\n", before);
	if (!check_print_error(before, after, key_w_skip))
		return (NULL);
	printf("beforeeeee %s\n", before);
	printf("afterrrrrr %s\n", after);
	arr = malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup(before);
	arr[1] = ft_strdup(after);
	free(before);
	free(after);
	return (arr);
}

//export abc =5

//firstly check for key after that, check value
void	ft_export(t_node *command)
{
	/* char	*str1;
	char	*str2;
	char	*key; */
	int		index;
	
	process_str_exp(command, &command->fcmd);
	printf("Processed fcmd-> %s\n", command->fcmd);
	if (!ft_strchr(command->fcmd, '='))
		return ;
	char	**split = check_invalid_identifier(command->fcmd);
	if (!split)
		return ;
	index = index_from_key(split[0], command->shell->env);
	printf("index is -> %d\n", index);
	if (index == -1)
		create_and_set_val(command->shell, split[0], split[1]);
	else
		change_env_value(split[0], split[1] + 1, command->shell);
	/* if (index_from_key(split[0], command->env) == -1)
		create_and_set_val(command->shell, split[0], split[1]); */
		//might need to change create set value func
}

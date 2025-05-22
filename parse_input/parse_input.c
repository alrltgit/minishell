/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/22 17:17:17 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int alloc_mem_for_flags_arr(t_node *current_node)
{
    if (current_node->flags_count > 0)
    {
        current_node->flags = malloc(sizeof(char *) * (current_node->flags_count + 1));
        if (!current_node->flags)
            return (1);
    }
    else
    {
        current_node->flags = malloc(sizeof(char *));
        if (!current_node->flags)
            return (1);
        current_node->flags[0] = NULL;
    }
    return (0);
}

// int file_exists(t_node *current_node, char **result, int *j)
// {
//     if (access(current_node->file_name, F_OK) != 0)
//     {
//         printf("%s: No such file or directory.\n", result[*j]);
//         return (1);
//     }
//     if (access(current_node->file_name, R_OK) != 0)
//     {
//         printf("%s: Permission denied.\n", result[*j]);
//         return (1);
//     }
//     return (0);
// }

void add_new_file(t_node *current_node, char *result)
{
    // current_node->redir_files->file_name = malloc(sizeof(char) * (ft_strlen(result) + 1));
    if (!current_node->redir_files->file_name)
        return ;
    current_node->redir_files->file_name = ft_strdup(result);
    current_node->redir_files->next = NULL;
}

int add_cmds_flags_to_linked_list(char **result, t_node **unit)
{
    t_node *current_node;
    int i;
    int j;
    int j_temp;
    int cmd_is_found;

    cmd_is_found = 0;
    current_node = *unit;
    j = 0;
    j_temp = j;
    current_node->flags_count = count_flags(result, j_temp);
    if (alloc_mem_for_flags_arr(current_node) == 1)
        return (1);
    current_node->redir_files = malloc(sizeof(t_redir));
    init_t_redir(current_node);
    i = 0;
    while (result[j])
    {
        if (ft_strcmp(result[j], "|") == 0)
        {
            current_node->is_pipe = 1;
            current_node = add_unit_to_end(unit);
            j_temp = j;
            j_temp++;
            if (!result[j_temp])
                return (1);
            current_node->flags_count = count_flags(result, j_temp);
            if (current_node->flags_count > 0)
            {
                current_node->flags = malloc(sizeof(char *) * (current_node->flags_count + 1));
                if (!current_node->flags)
                    return (1);
            }
            else
            {
                current_node->flags = malloc(sizeof(char *));
                if (!current_node->flags)
                    return (1);
                current_node->flags[0] = NULL;
            }
            i = 0;
            cmd_is_found = 0;
            j++;
        }
        if (ft_strcmp(result[i], "<") == 0)
        {
            current_node->redir_files->file_name = malloc(sizeof(char) * (ft_strlen(result[i]) + 1))
        }
        if (cmd_is_found == 0)
            current_node->cmd_type = find_command_path(result[j], current_node, &cmd_is_found);
        if (cmd_is_found == 0)
        {
            printf("%s: command not found\n", result[j]);
            return (1);
        }
        if (current_node->flags_count > 0)
            find_flags(result[j], current_node, &i);
        j++;
    }
    return (0);
}

void add_args_to_linked_list(char **result, t_node **unit)
{
    int 	i;
    int 	j;
    t_node *current_node;

    j = 0;
    current_node = *unit;
    current_node->args_count = count_args(result, current_node);
    current_node->args = malloc(sizeof(char *) * current_node->args_count + 1);
    i = 0;
    while (result[i])
    {
        if (ft_strcmp(result[i], "|") == 0)
        {
            j = 0;
            current_node = current_node->next;
            if (!current_node)
                break ;
            current_node->args_count = count_args_inside_loop(result, current_node, &i);
            current_node->args = malloc(sizeof(char *) * current_node->args_count + 1);
            if (!current_node->args)
                return ;
            i++;
        }
        if (current_node && result[i])
            find_args(current_node, result, &i, &j);
        i++;
    }
}

void read_the_input(char *rl, t_shell *shll)
{
    char	**result;
    t_node 	*unit;
    t_node 	*temp;

	if (ft_strcmp(rl, "") == 0 || rl_is_space(rl) == 0)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
		return ;
	}
    result = split_args(rl);
    unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
	temp = unit;
    if (add_cmds_flags_to_linked_list(result, &temp) == 1)
        return ;
    else if (add_cmds_flags_to_linked_list(result, &temp) == 0)
        add_args_to_linked_list(result, &temp);
    int i;
    while (temp)
    {
        printf("temp->cmd: %s\n", temp->cmd);
        i = 0;
        while (i++ < temp->flags_count)
            printf("temp->flags[i]: %s\n", temp->flags[i]);
        
        i = 0;
        while (i++ < temp->args_count)
            printf("temp->args[i]: %s\n", temp->args[i]);
        temp = temp->next;
    }
    if (unit->is_pipe)
        create_pipe(unit);
    else
    {
        if (unit->cmd_type == B_IN)
            execute_builtin(unit);
        else if (unit->cmd_type == NON_B_IN)
        {
            execute_other(unit);
        }
        else
        {
            ft_printf("%s", result[0]);
			ft_putstr_fd(" : command not found\n", 2);
        }
    }
    free_arr(result);
	// free_node_arr(unit->flags, unit->flags_count);
	// free_node_arr(unit->args, unit->args_count);
	// free(unit->cmd);
    // free_linked_list(unit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:49 by apple             #+#    #+#             */
/*   Updated: 2025/05/10 13:08:49 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void add_cmds_flags_to_linked_list(char **result, t_node **unit)
{
    t_node *current_node;
    int		i;
    int		j;
    int		cmd_is_found;

    i = 0;
    j = 0;
    cmd_is_found = 0;
    current_node = *unit;
    current_node->flags_count = count_flags(result);
    current_node->flags = malloc(sizeof(char *) * current_node->flags_count);
    if (!current_node->flags)
        return ;
    while (result[j])
    {
        if (is_operator(result[j]))
        {
            current_node = add_unit_to_end(unit);
            current_node->flags_count = count_flags(result);
            current_node->flags = malloc(sizeof(char *) * current_node->flags_count);
            if (!current_node->flags)
                return ;
            i = 0;
            cmd_is_found = 0;
            j++;
            continue ;
        }
        if (cmd_is_found == 0)
            find_command_path(result[j], current_node, &cmd_is_found);
        find_flags(result[j], current_node, &i);
        j++;
    }
}

void add_args_to_linked_list(char **result, t_node *unit)
{
    int i;
    int j;

    unit->args = malloc(sizeof(char *) * unit->args_count);
    if (!unit->args)
        return ;
    i = 0;
    j = 0;
    while (result[j])
    {
        if (is_operator(result[j]))
        {
            break ;
        }
        find_args(unit, result, &i, &j);
        j++;
    }
}

/*
 command process

 is_valid => is_builtin 
 yes => execute related builtin, set cmd->isbuiltin = 1
 no => execute other
*/
void read_the_input(char *rl, t_shell *shll)
{
    char **result;
    t_node *unit;
    
    result = split_args(rl);
    unit = create_unit();
	unit->shell = shll;
	shll->cmds = unit;
    add_cmds_flags_to_linked_list(result, &unit);
    unit->args_count = count_args(unit, result);
    add_args_to_linked_list(result, unit);
	/* if (!is_valid_command)
	{
		ft_putstr_fd(ft_strconcat(rl, ": command not found"), 2);
		shll->errcode = 1;
		set proper exit (maybe return;)
		so according to errcode, it can exit
	} */
	//if (is_builtin())
	//	execute_builtin()
	/*else
		execute_other() */
    free(result);
}

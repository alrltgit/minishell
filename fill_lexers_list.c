/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexers_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:05:51 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/06 14:19:54 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_lexer *create_node(char *data)
{
    t_lexer *node;

    node = malloc(sizeof(t_lexer));
    if (!node)
        return (NULL);
    node->data = data;
    node->next = NULL;
    return (node);
}

t_lexer *add_node_to_end(t_lexer **head, char *data)
{
    t_lexer *temp;
    t_lexer *new_node;

    new_node = create_node(data);
    if (!new_node)
        return (NULL);
    if (!*head)
        return (new_node);
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
    return (*head);
}

t_lexer *add_lexers_to_list(char **rl)
{
    t_lexer *head;
    int i;

    head = create_node(rl[0]);
    if (!head)
        return (NULL);
    i = 1;
    while (rl[i])
    {
        head = add_node_to_end(&head, rl[i]);
        // printf("lexer: %s\n", lexer->lexer);
        i++;
    }
    return (head);
}

void add_to_unit_cmd(t_lexer *input, t_unit *unit)
{
    t_lexer *temp;
    int i;
    int cmd_is_found;

    i = 0;
    cmd_is_found = 0;
    temp = input;
    unit->data->cmd = NULL;
    unit->data->flags = malloc(sizeof(char *) * unit->data->flags_count);
    if (!unit->data->flags)
        return ;
    while (temp)
    {
        printf("temp->data: %s\n", temp->data);
        if (ft_strcmp(temp->data, "|") == 0 || ft_strcmp(temp->data, "<") == 0
            || ft_strcmp(temp->data, ">") == 0 || ft_strcmp(temp->data, ">>") == 0
            || ft_strcmp(temp->data, "<<") == 0)
            break ;
        if (cmd_is_found == 0)
            unit->data->cmd = find_command_path(temp->data, unit, &cmd_is_found);
        find_flags(temp, unit, &i);
        temp = temp->next;
    }
}

void read_the_input(char *rl, t_lexer *input)
{
    char **result;
    t_unit *unit;
    
    result = split_args(rl);
    input = add_lexers_to_list(result);
    if (!input)
        return ;
    unit = malloc(sizeof(t_unit));
    unit->data = malloc(sizeof(t_node));
    unit->data->flags_count = count_flags(input);
    // printf("flags_count: %d\n", unit->data->flags_count);
    add_to_unit_cmd(input, unit);
    printf("unit->data->cmd: %s\n", unit->data->cmd);
    int i = 0;
    while (i < unit->data->flags_count)
    {
        printf("unit->data->flags[%d]: %s\n", i, unit->data->flags[i]);
        i++;
    }
    free(result);
}
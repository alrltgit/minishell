/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexers_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:05:51 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/06 13:30:49 by apple            ###   ########.fr       */
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

void divide_into_nodes(t_lexer *input, t_unit *unit)
{
    t_lexer *temp;

    temp = input;
    unit->data->cmd = NULL;
    while (temp)
    {
        printf("temp->data: %s\n", temp->data);
        if (ft_strcmp(temp->data, "|") == 0 || ft_strcmp(temp->data, "<") == 0
            || ft_strcmp(temp->data, ">") == 0 || ft_strcmp(temp->data, ">>") == 0
            || ft_strcmp(temp->data, "<<") == 0)
            break ;
        unit->data->cmd = find_command_path(temp->data);
        printf("unit->data->cmd: %s\n", unit->data->cmd);
        if (unit->data->cmd)
            break ;
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
    divide_into_nodes(input, unit);
    free(result);
}
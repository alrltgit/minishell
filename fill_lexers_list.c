/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexers_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:05:51 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/05 15:58:00 by alraltse         ###   ########.fr       */
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

void divide_into_nodes(t_lexer *input, t_node *node)
{
    t_lexer *temp;

    temp = input;
    while (temp)
    {
        printf("temp->data: %s\n", temp->data);
        if (ft_strcmp(temp->data, "|") == 0 || ft_strcmp(temp->data, "<") == 0
            || ft_strcmp(temp->data, ">") == 0 || ft_strcmp(temp->data, ">>") == 0
            || ft_strcmp(temp->data, "<<") == 0)
            break ;
        node->cmd = find_command_path(temp->data);
        printf("node->cmd: %s\n", node->cmd);
        if (node->cmd)
            break ;
        temp = temp->next;
    }
}

void count_flags(t_node *node)
{
    
}

void read_the_input(char *rl, t_lexer *input)
{
    char **result;
    t_node *node;
    
    result = split_args(rl);
    input = add_lexers_to_list(result);
    if (!input)
        return ;
    node = malloc(sizeof(t_node));
    divide_into_nodes(input, node);
    // find_operators(input, node);
    // while (input)
    // {
    //     // printf("input->data: %s\n", input->data);
    //     input = input->next;
    // }
    free(result);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexers_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:05:51 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/04 19:13:49 by apple            ###   ########.fr       */
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

void read_the_input(char *rl, t_lexer *lexers)
{
    char **result;
    t_ast *ast;
    
    result = split_args(rl);
    lexers = add_lexers_to_list(result);
    if (!lexers)
        return ;
    ast = malloc(sizeof(t_ast));
    find_command_path(lexers, ast);
    find_operators(lexers, ast);
    // while (lexers)
    // {
    //     printf("lexers: %s\n", lexers->data);
    //     lexers = lexers->next;
    // }
    // int i = 0;
    // while (result[i])
    // {
    //     printf("%s\n", result[i]);
    //     i++;
    // }
    free(result);
}
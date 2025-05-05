/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:08 by apple             #+#    #+#             */
/*   Updated: 2025/05/04 19:24:42 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void find_operators(t_lexer *lexers,  t_ast *ast)
{
    t_lexer *temp;

    temp = lexers;
    ast->operators = NULL;
    while (temp)
    {
        if (temp->data == '+' || temp->data == '-' || temp->data == '*'
            || temp->data == '/' || temp->data == '%' || temp->data == "**")
        temp = temp->next;
    }
    // while (temp)
    // {
    //     printf("temp->data: %s\n", temp->data);
    //     temp = temp->next;
    // }
}
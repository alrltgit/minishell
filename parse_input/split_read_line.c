/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:39:40 by alraltse          #+#    #+#             */
/*   Updated: 2025/05/12 13:08:18 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void skip_whitespace(const char *str, int *i)
{
    while (str[*i] == ' ')
        (*i)++;
}

static void trim_quotes_if_needed(char *token, int len)
{
    if ((token[0] == '\'' && token[len - 1] == '\'') 
            || (token[0] == '"' && token[len - 1] == '"'))
    {
            token[len - 1] = '\0';
            ft_memmove(token, token + 1, len - 1);
    }
}

static char *extract_token(const char *str, int *i)
{
    int start;
    int single_q;
    int double_q;
    int len;
    char *token;

    start = *i;
    single_q = 0;
    double_q = 0;
    while (str[*i])
    {
        if (str[*i] == '\'' && !double_q)
            single_q = !single_q;
        else if (str[*i] == '"' && !single_q)
            double_q = !double_q;
        else if ((str[*i] == ' ' || str[*i] == '\t') && !single_q && !double_q)
            break ;
        (*i)++;
    }
    len = *i - start;
    token = ft_substr(str, start, len);
    if (!token)
        return (NULL);
    trim_quotes_if_needed(token, len);
    return (token);
}

char **split_args(char *str)
{
    char **result;
    char *token;
    int i;
    int count;

    result = malloc(sizeof(char *) * 1024);
    if (!result)
        return (NULL);
    i = 0;
    count = 0;
    while (str[i])
    {
        skip_whitespace(str, &i);
        if (!str[i])
            break ;
        token = extract_token(str, &i);
        if (!token)
            return (NULL);
        result[count++] = token;
    }
    result[count] = NULL;
    return (result);
}

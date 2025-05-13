/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:06 by hceviz            #+#    #+#             */
/*   Updated: 2025/05/12 14:48:04 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcat(char *s1, char *s2)
{
    int i;
    int j;
    char *result;

    result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[i])
        result[j++] = s1[i++];
    i = 0;
    while (s2[i])
        result[j++] = s2[i++];
    result[j] = '\0';
    return (result);
}
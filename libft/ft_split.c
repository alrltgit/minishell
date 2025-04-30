/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alraltse <alraltse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:35:13 by apple             #+#    #+#             */
/*   Updated: 2025/04/08 16:52:14 by alraltse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_word(const char *str, int *start, int end)
{
	char	*word;
	int		k;
	int		i;
	int		diff;

	k = *start;
	i = 0;
	diff = end - k;
	word = malloc((diff + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (k < end)
	{
		word[i] = str[k];
		i++;
		k++;
	}
	word[i] = '\0';
	*start = end + 1;
	return (word);
}

static char	**array_length_count(char const *s, char c)
{
	int		strings_nb;
	int		delim;
	int		i;
	char	**array;

	strings_nb = 0;
	delim = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && delim == 0)
		{
			delim = 1;
			strings_nb++;
		}
		else if (s[i] == c)
			delim = 0;
		i++;
	}
	array = malloc((strings_nb + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	return (array);
}

static char	*free_mem(char **array, int j)
{
	while (j > 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		s_word;
	int		j;
	size_t	i;

	array = array_length_count(s, c);
	s_word = -1;
	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			array[j] = fill_word(s, &s_word, i);
			if (!array[j])
				free_mem(array, j);
			j++;
			s_word = -1;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}

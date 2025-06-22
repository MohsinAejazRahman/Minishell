/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:49:16 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/10 13:00:36 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			count++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
		else if (*(s + i) == c)
			i++;
	}
	return (count);
}

static size_t	get_word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	free_array(size_t i, char **array)
{
	while (i--)
	{
		free(*(array + i));
	}
	free(array);
}

static char	**main_split_work(char const *s, char c,
		char **array, size_t tot_words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < tot_words)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(array + i) = ft_substr(s, j, get_word_len(&*(s + j), c));
		if (!*(array + i))
		{
			free_array(i, array);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**split_arr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	split_arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split_arr)
		return (NULL);
	split_arr = main_split_work(s, c, split_arr, words);
	return (split_arr);
}

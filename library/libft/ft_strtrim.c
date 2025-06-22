/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:01:59 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/09 13:40:26 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_len(char const *str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

static size_t	is_set_char(char const *str, char c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (*(s1 + start) && is_set_char(set, *(s1 + start)))
		start++;
	end = str_len(s1);
	while (end > start && is_set_char(set, *(s1 + (end - 1))))
		end--;
	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while ((start + i) < end)
	{
		*(res + i) = *(s1 + (start + i));
		i++;
	}
	*(res + i) = '\0';
	return (res);
}

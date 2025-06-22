/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:26:14 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/09 12:39:55 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_len(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (str_len(s1) + str_len(s2) + 1));
	if (!str)
		return (NULL);
	while (*(s1 + i))
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	while (*(s2 + j))
	{
		*(str + i) = *(s2 + j);
		i++;
		j++;
	}
	*(str + i) = '\0';
	return (str);
}

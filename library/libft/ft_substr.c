/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:10:17 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/08 21:16:10 by skhastag         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*subs;

	i = 0;
	if (start > str_len(s))
		len = 0;
	else if (len > (str_len(s) - start))
		len = str_len(s) - start;
	subs = (char *)(malloc(sizeof(char) * (len + 1)));
	if (!subs)
		return (NULL);
	while (len > 0 && *(s + start + i))
	{
		*(subs + i) = *(s + start + i);
		i++;
		len--;
	}
	*(subs + i) = '\0';
	return (subs);
}

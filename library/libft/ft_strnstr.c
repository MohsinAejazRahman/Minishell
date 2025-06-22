/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:00:03 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/06 20:28:38 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *to_find, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(src + i) && !size)
		return (NULL);
	if (!*(to_find + i))
		return ((char *)src);
	while (*(src + i) && size--)
	{
		j = 0;
		while (*(src + i + j) == *(to_find + j)
			&& *(to_find + j) && j <= size)
		{
			if (!*(to_find + j + 1))
				return ((char *)(src + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

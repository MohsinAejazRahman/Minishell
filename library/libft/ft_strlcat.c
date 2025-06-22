/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:40 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/12 12:04:25 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		dest_has_len;
	size_t		total_len;
	int			i;

	i = 0;
	if ((!dest || !src) && !size)
		return (0);
	dest_has_len = 0;
	while (*(dest + dest_has_len) && dest_has_len < size)
		dest_has_len++;
	if (dest_has_len < size)
		total_len = dest_has_len + ft_strlen(src);
	else
		return (size + ft_strlen(src));
	while (*(src + i) && dest_has_len < size - 1)
	{
		*(dest + dest_has_len) = *(src + i);
		dest_has_len++;
		i++;
	}
	*(dest + dest_has_len) = '\0';
	return (total_len);
}

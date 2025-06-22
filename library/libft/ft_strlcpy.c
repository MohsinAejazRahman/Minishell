/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:32 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/06 16:04:26 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (*(src + c))
	{
		c++;
	}
	if (size < 1)
	{
		return (c);
	}
	while (*(src + i) && i < size - 1)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = 0;
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:40:23 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/08 12:42:05 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove( void *dest, const void *src, size_t count )
{
	int	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	if (dest > src)
	{
		while (count--)
		{
			*((char *)dest + count) = *((char *)src + count);
			i++;
		}
	}
	else
	{
		while (count--)
		{
			*((char *)dest + i) = *((char *)src + i);
			i++;
		}
	}
	return ((void *)dest);
}

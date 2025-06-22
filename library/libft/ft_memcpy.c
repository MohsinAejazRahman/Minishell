/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:29:19 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/08 09:34:46 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	int	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (count > 0)
	{
		*((char *)dest + i) = *((char *)src + i);
		count--;
		i++;
	}
	return ((void *)(char *)dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:28:01 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/08 18:13:49 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = malloc(size * num);
	if (!dest)
		return (NULL);
	while (i < (num * size))
	{
		*((unsigned char *)dest + i) = 0;
		i++;
	}
	return ((void *)dest);
}

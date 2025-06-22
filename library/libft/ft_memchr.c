/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:53:32 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/07 15:01:09 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *str, int c, size_t len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		if (*((unsigned char *)str + i) == (unsigned char)c)
			return (((void *)(unsigned char *)str + i));
		len--;
		i++;
	}
	return (NULL);
}

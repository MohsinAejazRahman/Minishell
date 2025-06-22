/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:43:51 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/07 15:12:15 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	int		i;

	i = 0;
	while (len > 0)
	{
		*((unsigned char *)str + i) = (unsigned char) c;
		i++;
		len--;
	}
	return ((void *)(unsigned char *)str);
}

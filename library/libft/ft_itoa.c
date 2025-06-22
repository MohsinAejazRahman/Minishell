/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:01:39 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/09 17:12:37 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	n_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				len;
	char			*str;

	nbr = n;
	if (n < 0)
		nbr = n * (-1);
	len = n_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	while (len--)
	{
		*(str + len) = 48 + (nbr % 10);
		nbr /= 10;
	}
	if (n < 0)
		*(str) = 45;
	return (str);
}

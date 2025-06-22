/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:01:23 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/10 20:59:39 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*(s1 + i) && *(s2 + i)
		&& (unsigned char)(*(s1 + i)) == (unsigned char)(*(s2 + i))
		&& n > 1)
	{
		i++;
		n--;
	}
	return ((unsigned char)(*(s1 + i)) - (unsigned char)(*(s2 + i)));
}

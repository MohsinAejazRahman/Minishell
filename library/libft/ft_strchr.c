/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:03:15 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:52 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *str, int ch)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == (char)ch)
			return ((char *)(str + i));
		i++;
	}
	if (*(str + i) == (char)ch)
		return ((char *)(str + i));
	else
		return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:48:42 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/08 16:21:18 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, int ch)
{
	int			i;
	const char	*flag;

	i = 0;
	flag = NULL;
	while (*(str + i))
	{
		if (*(str + i) == (char)ch)
			flag = (str + i);
		i++;
	}
	if (*(str + i) == (char)ch)
		return ((char *)(str + i));
	else
		return ((char *)flag);
}

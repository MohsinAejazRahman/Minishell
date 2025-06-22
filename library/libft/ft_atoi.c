/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:34:11 by skhastag          #+#    #+#             */
/*   Updated: 2024/05/22 01:34:36 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_space(int ch)
{
	if ((ch && ch == ' ') || ((ch >= 9 && ch <= 13)))
		return (1);
	return (0);
}

static int	ft_check_digit(int ch)
{
	if (ch > 47 && ch < 58)
		return (1);
	return (0);
}

static int	ft_check_sign(const char *str, int *index)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	if (*(str + i) && (*(str + i) == '-' || *(str + i) == '+'))
	{
		if (*(str + i) == '-')
			sign *= -1;
		*index = *index + 1;
		i++;
	}
	return (sign);
}

int	ft_atoi(char const *str)
{
	int	result;
	int	check;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (*(str + i) && ft_check_space(*(str + i)))
		i++;
	sign = ft_check_sign((str + i), &i);
	while (*(str + i) && ft_check_digit(*(str + i)))
	{
		check = result;
		result = result * 10 + sign * (*(str + i) - '0');
		if (result > check && sign < 0)
			return (0);
		if (result < check && sign > 0)
			return (-1);
		i++;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_terminal_utils_extra.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:04:02 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/09 21:19:34 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_hostname(t_hostname *hostname)
{
	int	i;

	if (hostname->cmd_args)
	{
		i = 0;
		while (hostname->cmd_args[i])
		{
			null_check_free_str(hostname->cmd_args[i]);
			i++;
		}
		null_check_free_str(hostname->cmd_args[1]);
		free_2d(hostname->cmd_args);
	}
	if (hostname->res)
		null_check_free_str(hostname->res);
}

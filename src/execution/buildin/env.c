/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:03:39 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/12 19:14:49 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_env(t_minishell_data *mini)
{
	int		i;

	i = -1;
	if (ft_strncmp(mini->cmds->args[0], "env", 4) == 0)
	{
		while (mini->envp[++i] != NULL)
			if (ft_strchr(mini->envp[i], '=') != NULL)
				ft_putendl_fd(mini->envp[i], mini->out_fd);
		mini->exit_cd = 0;
	}
	else
		error_print_one_message(mini->cmds->args[0], 1, mini);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:03:47 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/12 19:17:14 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_pwd(t_minishell_data *mini)
{
	char	*cwd;

	if (ft_strncmp(mini->cmds->args[0], "pwd",
			ft_strlen(mini->cmds->args[0])) == 0)
	{
		cwd = getcwd(NULL, 0);
		ft_putendl_fd(cwd, mini->out_fd);
		null_check_free_str(cwd);
		mini->exit_cd = 0;
	}
	else
		error_print_one_message(mini->cmds->args[0], 1, mini);
}

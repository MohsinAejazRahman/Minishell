/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:47:52 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/13 04:45:10 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	execution_manager(t_minishell_data *mini)
{
	if (ft_strncmp(mini->cmds->args[0], "&&", 3) == 0)
		error_print(mini->cmds->args[0], mini);
	else if (ft_strncmp(mini->cmds->args[0], "exit", 5) == 0)
		ft_exit(mini);
	else if (ft_lstsize_commands(mini->cmds) == 1)
		single_execution(mini);
	else if (ft_lstsize_commands(mini->cmds) > 1)
		multiple_execution(mini);
	else
		error_print_one_message(mini->cmds->args[0], 1, mini);
}
/*
 *cd pwd echo env can be capital also
 */

void	reset_in_and_out_single(t_minishell_data *mini, int i)
{
	dup2(mini->fds[i][0], STDIN_FILENO);
	dup2(mini->fds[i][1], STDOUT_FILENO);
	free_fd(mini->fds, 2);
}

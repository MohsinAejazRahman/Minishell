/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:54:23 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/06 17:23:16 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	buildin_manager_check(t_minishell_data *mini)
{
	if (ft_strncmp(mini->cmds->args[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(mini->cmds->args[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(mini->cmds->args[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(mini->cmds->args[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(mini->cmds->args[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(mini->cmds->args[0], "export", 6) == 0)
		return (1);
	return (0);
}

void	buildin_manager(t_minishell_data *mini)
{
	if (ft_strncmp(mini->cmds->args[0], "cd", \
		ft_strlen(mini->cmds->args[0])) == 0)
		ft_cd(mini);
	else if (ft_strncmp(mini->cmds->args[0], "pwd", \
		ft_strlen(mini->cmds->args[0])) == 0)
		ft_pwd(mini);
	else if (ft_strncmp(mini->cmds->args[0], "echo", \
		ft_strlen(mini->cmds->args[0])) == 0)
		ft_echo(mini, 1);
	else if (ft_strncmp(mini->cmds->args[0], "env", \
		ft_strlen(mini->cmds->args[0])) == 0)
		ft_env(mini);
	else if (ft_strncmp(mini->cmds->args[0], "unset", \
		ft_strlen(mini->cmds->args[0])) == 0)
		ft_unset(mini);
	else if (ft_strncmp(mini->cmds->args[0], "export", \
		ft_strlen(mini->cmds->args[0])) == 0)
		ft_export(mini);
}

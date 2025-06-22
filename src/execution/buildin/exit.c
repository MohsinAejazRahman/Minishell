/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:03:42 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/14 01:50:33 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

long long	ft_atoll(const char *str)
{
	long long	i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	result = 0;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

int	isnum_str(char *s)
{
	int	flag;
	int	i;

	i = -1;
	flag = 0;
	while (s[++i] != '\0')
	{
		if ((!ft_isdigit(s[i]) && s[i] != '+' && s[i] != '-') || flag > 1)
			return (0);
		if (s[i] == '+' || s[i] == '-')
			flag++;
	}
	return (1);
}

void	ft_exit_system(t_minishell_data *mini, int c)
{
	(void)mini;
	ft_putendl_fd("exit", 1);
	exit(c);
}

void	ft_exit(t_minishell_data *mini)
{
	ft_update_shell_level(mini, 0);
	if (ft_strncmp(mini->cmds->args[0], "exit", 5) != 0)
		error_print_one_message(mini->cmds->args[0], 1, mini);
	else if (check_envp_len(mini->cmds->args) > 1
		&& !isnum_str(mini->cmds->args[1]))
	{
		ft_putendl_fd("exit", 1);
		error_print_message("exit: ", mini->cmds->args[1], 1, mini);
	}
	else if (check_envp_len(mini->cmds->args) == 1
		&& ft_strncmp(mini->cmds->args[0], "exit", 5) == 0)
		ft_exit_system(mini, mini->exit_cd);
	else if (check_envp_len(mini->cmds->args) == 2
		&& ft_strncmp(mini->cmds->args[0], "exit", 5) == 0)
		ft_exit_system(mini, ft_atoll(mini->cmds->args[1]));
	else if (check_envp_len(mini->cmds->args) > 2
		&& isnum_str(mini->cmds->args[1]))
		error_print_message("exit", NULL, 2, mini);
	else
		error_print_one_message(mini->cmds->args[0], 1, mini);
}

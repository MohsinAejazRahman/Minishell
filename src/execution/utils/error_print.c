/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 06:50:02 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/09 22:21:40 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	error_print_one_message(char *message, int c, t_minishell_data *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	if (c == 1)
	{
		ft_putendl_fd(": command not found", 2);
		mini->exit_cd = 127;
	}
	else if (c == 2)
	{
		ft_putendl_fd(": No such file or directory", 2);
		mini->exit_cd = 1;
	}
	else if (c == 3)
	{
		ft_putendl_fd(": not enough arguments", 2);
		mini->exit_cd = 1;
	}
	else if (c == 4)
	{
		ft_putendl_fd(": HOME not set", 2);
		mini->exit_cd = 1;
	}
}

void	error_print_message(char *message1, char *message2, int c,
		t_minishell_data *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message1, 2);
	if (message2 != NULL)
		ft_putstr_fd(message2, 2);
	if (c == 1)
	{
		ft_putendl_fd(": numeric argument required", 2);
		free_mini_dto(mini);
		exit(255);
	}
	else if (c == 2)
	{
		ft_putendl_fd(": too many arguments", 2);
		mini->exit_cd = 1;
	}
	else if (c == 3)
	{
		ft_putendl_fd(": OLDPWD not set", 2);
		mini->exit_cd = 1;
	}
	else if (c == 4)
	{
		ft_putendl_fd(": HOME not set", 2);
		mini->exit_cd = 1;
	}
}

void	error_print_two_message(char *message1, char *message2, int c,
		t_minishell_data *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message1, 2);
	ft_putstr_fd(message2, 2);
	if (c == 1)
	{
		ft_putendl_fd(": command not found", 2);
		mini->exit_cd = 127;
	}
	else if (c == 2)
	{
		ft_putendl_fd(": No such file or directory", 2);
		mini->exit_cd = 1;
	}
	else if (c == 3)
	{
		ft_putendl_fd(": not enough arguments", 2);
		mini->exit_cd = 1;
	}
	else if (c == 4)
	{
		ft_putendl_fd("': not a valid identifier", 2);
		mini->exit_cd = 1;
	}
}

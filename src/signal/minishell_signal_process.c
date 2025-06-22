/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:18:30 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/12 01:25:37 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler_init(t_minishell_data *mini_dto)
{
	(void)mini_dto;
	signal(SIGINT, sigquit_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	signal_handler_end(t_minishell_data *mini_dto)
{
	(void)mini_dto;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler(int sig)
{
	char	*temp;

	(void)sig;
	temp = ft_strjoin(rl_line_buffer, "  ");
	rl_replace_line(temp, 0);
	free(temp);
	rl_redisplay();
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3", 1);
	ft_putchar_fd('\n', 1);
}

int	handle_termios(void)
{
	int				status;
	struct termios	term;

	status = tcgetattr(STDIN_FILENO, &term);
	if (status == -1)
	{
		ft_putstr_fd("failed tcgetattr", 2);
		return (1);
	}
	term.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDIN_FILENO, TCSANOW, &term);
	if (status == -1)
	{
		ft_putstr_fd("failed tcsetattr", 2);
		return (1);
	}
	return (0);
}

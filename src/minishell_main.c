/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:16:10 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/12 01:21:08 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Avoid using more than one global variable to indicate
 a received signal. Consider
the implications: this approach ensures that your
 signal handler will not access your
main data structures.
*/
int	g_global_sig = 0;

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell_data	minishell_data;
	int					exit_cod;

	(void)argv;
	exit_cod = 1;
	if (argc != 1 || !*envp)
		return (exit_cod);
	signal_handler_end(&minishell_data);
	init_mini_data(&minishell_data, envp);
	rl_bind_key('\t', rl_complete);
	using_history();
	init_terminal(&minishell_data);
	clear_history();
	return (exit_cod = minishell_data.exit_cd, printf("exit\n"), exit_cod);
}

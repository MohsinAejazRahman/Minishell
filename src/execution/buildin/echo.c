/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:03:37 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/13 01:20:41 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_echo_n_check(char *s)
{
	int	i;

	if (ft_strncmp(s, "-n", 2) == 0)
	{
		i = 1;
		while (s[++i] != '\0' && s[0] == '-' && s[i] == 'n')
			if (s[i] != 'n' && i > 1)
				return (0);
		if (i == (int)ft_strlen(s))
			return (1);
	}
	return (0);
}

void	ft_echo_nl(t_minishell_data *mini, int flag1)
{
	if (flag1 != 0)
		ft_putstr_fd("\n", mini->out_fd);
	mini->exit_cd = 0;
}

void	ft_echo_print_tilda(t_minishell_data *mini)
{
	char	*print;
	char	*home;
	int		i;
	int		j;

	home = getenv("HOME=");
	i = ft_strlen(home);
	while (i > -1 && home[i] != '=')
		i--;
	print = malloc(ft_strlen(home) - i);
	j = -1;
	while (home[++i] != '\0')
		print[++j] = home[i];
	print[++j] = '\0';
	ft_putstr_fd(print, mini->out_fd);
	free(print);
}

void	ft_echo_print(t_minishell_data *mini, int i)
{
	if (ft_strncmp(mini->cmds->args[i], "~", 2) == 0)
		ft_echo_print_tilda(mini);
	else
		ft_putstr_fd(mini->cmds->args[i], mini->out_fd);
}

void	ft_echo(t_minishell_data *mini, int flag2)
{
	int	flag1;
	int	i;

	i = 0;
	flag1 = 1;
	if (ft_strncmp(mini->cmds->args[0], "echo", 5) == 0)
	{
		while (mini->cmds->args[++i] != NULL)
		{
			if (ft_echo_n_check(mini->cmds->args[i]) && flag2 != 0)
				flag1 = 0;
			else
			{
				flag2 = 0;
				ft_echo_print(mini, i);
				if (mini->cmds->args[i + 1] == NULL)
					break ;
				ft_putstr_fd(" ", mini->out_fd);
			}
		}
		ft_echo_nl(mini, flag1);
	}
	else
		error_print_one_message(mini->cmds->args[0], 1, mini);
}

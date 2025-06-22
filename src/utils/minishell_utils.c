/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:07:59 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/13 02:08:20 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_envp_len(char *envp[])
{
	int	i;

	i = -1;
	while (envp && envp[++i])
		;
	return (i);
}

void	init_mini_data(t_minishell_data *mini_dto, char *envp[])
{
	int	len;

	len = check_envp_len(envp);
	init_envp(envp, len, mini_dto);
	mini_dto->exit_cd = 0;
	mini_dto->out_fd = STDOUT_FILENO;
	mini_dto->in_fd = STDIN_FILENO;
	if (DEBUG)
	{
		ft_printf_2d(mini_dto->envp, "ENVIRONMENT VARIABLES");
		mini_dto->terminal_name = get_terminal_name_formated(mini_dto->envp);
	}
	else
		mini_dto->terminal_name = ft_strdup("minishell-0.1$ ");
}

int	ft_is_end_ch_envp(int ch)
{
	int	flag;

	flag = 1;
	if (!(ch >= 48 && ch <= 57) && !((ch >= 65 && ch <= 90) || (ch >= 97
				&& ch <= 122)) && ch != 95)
		flag = 0;
	return (flag);
}

void	ft_update_shell_level(t_minishell_data *mini, int i)
{
	char	*old_lvl_num;
	char	*new_lvl_num;

	old_lvl_num = get_value_after_equal(ft_getenv(mini, "SHLVL"));
	if (!old_lvl_num)
		return ;
	if (has_correct_value(old_lvl_num) == 1)
		new_lvl_num = ft_strdup("0");
	else if (has_correct_value(old_lvl_num) == 2)
		new_lvl_num = ft_strdup("1");
	else
	{
		if (i == 0)
		{
			new_lvl_num = ft_itoa(ft_atoi(old_lvl_num) - 1);
			if (ft_atoi(new_lvl_num) < 0)
				new_lvl_num = ft_strdup("0");
		}
		else if (i == 1)
			new_lvl_num = ft_itoa(ft_atoi(old_lvl_num) + 1);
		else
			new_lvl_num = ft_strdup("1");
	}
	old_lvl_num = ft_strjoin("SHLVL=", new_lvl_num);
	ft_update_shell_level_set_free(mini, old_lvl_num, new_lvl_num);
}

int	ft_env_stars_with_str(char *envp[], char *str)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}

/*
mini_dto->terminal_name = get_terminal_name_formated(mini_dto->envp);
	printf("%s\n",mini_dto->terminal_name);
	index = -1;
	while (++index < len)
		free (mini_dto->envp[index]);
	free (mini_dto->envp);
	free (mini_dto->terminal_name);
*/

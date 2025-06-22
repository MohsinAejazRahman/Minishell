/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_terminal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:57:02 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/13 07:19:08 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_print(char *s, t_minishell_data *mini)
{
	if (s[0] == '\"' && s[1] == '\"')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("", 2);
		ft_putendl_fd(": command not found", 2);
		mini->exit_cd = 127;
	}
	if (ft_strncmp(s, "&&", 3) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd("\'", 2);
		mini->exit_cd = 258;
	}
}

void	init_terminal(t_minishell_data *mini_dto)
{
	while (LOOP)
	{
		g_global_sig = 0;
		mini_dto->readline = readline(mini_dto->terminal_name);
		if (!mini_dto->readline)
			break ;
		if (mini_dto->readline[0] == '\0')
		{
			null_check_free_str(mini_dto->readline);
			continue ;
		}
		add_history(mini_dto->readline);
		if (is_ok_parsing(mini_dto) && mini_dto->cmds
			&& mini_dto->cmds->args && mini_dto->cmds->args[0])
			execution_manager(mini_dto);
		else
		{
			error_print(mini_dto->readline, mini_dto);
			null_check_free_str(mini_dto->readline);
			continue ;
		}
		if (mini_dto->readline)
			null_check_free_str(mini_dto->readline);
	}
	free_mini_dto(mini_dto);
}

void	init_envp(char *envp[], int len, t_minishell_data *mini_dto)
{
	int	index;

	index = -1;
	if (!ft_getenv_set(envp, "SHLVL"))
		mini_dto->envp = (char **)malloc(sizeof(char *) * len + 2);
	else
		mini_dto->envp = (char **)malloc(sizeof(char *) * len + 1);
	if (!mini_dto->envp)
		return (printf("Error: malloc failed\n"), free_mini_dto(mini_dto),
			exit(1));
	prepare_envp(envp, index, mini_dto, len);
}

void	prepare_envp(char *envp[], int index, t_minishell_data *mini_dto,
		int len)
{
	while (++index < len)
	{
		if (ft_env_stars_with_str(envp, "OLDPWD=") && ft_strncmp(envp[index],
				"OLDPWD", 6) == 0)
		{
			null_check_free_str(mini_dto->envp[index]);
			mini_dto->envp[index] = ft_strdup("OLDPWD");
		}
		else
			mini_dto->envp[index] = ft_strdup(envp[index]);
	}
	if (!ft_getenv(mini_dto, "SHLVL"))
	{
		mini_dto->envp[len] = ft_strdup("SHLVL=1");
		mini_dto->envp[len + 1] = NULL;
	}
	else
	{
		ft_update_shell_level(mini_dto, 1);
		mini_dto->envp[len] = NULL;
	}
}

int	has_correct_value(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			flag = 1;
		if (ft_isalpha(str[i]))
		{
			flag = 2;
			break ;
		}
	}
	return (flag);
}

/*
	char *line;
	char *newline;
else if	(ft_strncmp(mini_dto->readline + (ft_strlen(mini_dto->readline) - 1),
			"|", 1) == 0)
		{

			line = readline(">");
			while (line && line[0] == '\0')
			{
				add_history(line);
				free(line);
				line = readline(">");
			}
			newline = ft_strjoin(mini_dto->readline, line);
			free(mini_dto->readline);
			mini_dto->readline = newline;
		}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:02:32 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/12 18:08:27 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	has_value_after_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
		return (0);
	return (1);
}

int	ft_in_envp(char **envp, char *var)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& (envp[i][ft_strlen(var)] == '=' \
				|| envp[i][ft_strlen(var)] == '\0'
				|| (envp[i][ft_strlen(var)] == '+' && envp[i][ft_strlen(var)
					+ 1] == '=')))
			return (i);
	}
	return (0);
}

int	ft_expport_str_check(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0' && s[i] != '=' && !(s[i] == '+' && s[i + 1] == '='))
		if (ft_isalnum(s[i]) != 1 && s[i] != '_')
			return (0);
	return (1);
}

int	ft_export_error(t_minishell_data *mini, int i)
{
	if (mini->cmds->args[1][0] == '-')
	{
		if (i != 1)
			return (0);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("export: -", 2);
		ft_putchar_fd(mini->cmds->args[i][1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd(ERROR_EXPORT_MSG, 2);
		return (0);
	}
	else if (ft_isdigit(mini->cmds->args[i][0]) == 1)
	{
		error_print_two_message("export: `", mini->cmds->args[i], 4, mini);
		return (0);
	}
	else if (!ft_expport_str_check(mini->cmds->args[i]))
	{
		error_print_two_message("export: `", mini->cmds->args[i], 4, mini);
		return (0);
	}
	return (1);
}

char	*ft_get_env_var(char *env_line)
{
	char	*var;
	int		i;

	i = 0;
	while (env_line[i] != '\0' && env_line[i] != '+' && env_line[i] != '=')
		i++;
	var = malloc(i);
	i = -1;
	while (env_line[++i] != '\0' && env_line[i] != '+' && env_line[i] != '=')
		var[i] = env_line[i];
	var[i] = '\0';
	return (var);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:03:52 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/12 19:35:32 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_in_envp_unset(char **envp, char *var, int *j)
{
	*j = -1;
	while (envp[++(*j)] != NULL)
		if (ft_strncmp(var, envp[*j], ft_strlen(var)) == 0 && (envp[*j]
				[ft_strlen(var)] == '=' || envp[*j][ft_strlen(var)] == '\0'))
			return (*j);
	return (0);
}

int	ft_unset_str_check(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
		if (ft_isalnum(s[i]) != 1 && s[i] != '_')
			return (0);
	return (1);
}

int	ft_unset_error(t_minishell_data *mini)
{
	int	i;

	i = 0;
	while (mini->cmds->args[++i] != NULL)
	{
		if (ft_isdigit(mini->cmds->args[i][0]) == 1)
			error_print_two_message("unset: `", mini->cmds->args[i], 4, mini);
		else if (!ft_unset_str_check(mini->cmds->args[i]))
			error_print_two_message("unset: `", mini->cmds->args[i], 4, mini);
	}
	return (1);
}

void	ft_unset(t_minishell_data *mini)
{
	int	env_size;
	int	i;
	int	j;

	if (ft_strncmp(mini->cmds->args[0], "unset", 6) != 0)
		error_print_one_message("Unset: ", 1, mini);
	else if (mini->cmds->args[1] == NULL)
		return ;
	ft_unset_error(mini);
	i = 0;
	j = 0;
	while (mini->cmds->args[++i] != NULL)
	{
		if (ft_in_envp_unset(mini->envp, mini->cmds->args[i], &j) != 0)
		{
			env_size = check_envp_len(mini->envp);
			unshift_element(mini->envp, &j);
			mini->envp[env_size] = NULL;
		}
	}
	mini->exit_cd = ft_export_exit_calc(mini);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 03:15:07 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/11 22:44:43 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cd_back_size(char *cwd)
{
	int	i;

	i = ft_strlen(cwd) - 1;
	while (--i > -1)
		if (cwd[i] == '/')
			break ;
	if (i == 0)
		return (1);
	return (i);
}

char	*ft_cd_remove_tilda(char *s)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(s));
	i = 0;
	j = -1;
	while (++i < (int)ft_strlen(s) && ++j < i)
		result[j] = s[i];
	result[i] = '\0';
	return (result);
}

void	ft_cd_update_old_env(t_minishell_data *mini, char *owd)
{
	int	i;

	i = 0;
	if (ft_cd_minus_envp(mini->envp, "OLDPWD") > 0)
	{
		while (mini->envp[++i] != NULL && ft_strncmp(mini->envp[i], "OLDPWD=",
				7) != 0)
			i++;
		null_check_free_str(mini->envp[i]);
		mini->envp[i] = NULL;
		mini->envp[i] = ft_strjoin("OLDPWD=", owd);
		null_check_free_str(owd);
	}
	else
	{
		while (mini->envp[i] != NULL && ft_strncmp(mini->envp[i], "OLDPWD",
				7) != 0)
			i++;
		null_check_free_str(mini->envp[i]);
		mini->envp[i] = NULL;
		mini->envp[i] = ft_strjoin("OLDPWD=", owd);
		null_check_free_str(owd);
	}
}

void	ft_cd_new_pwd(t_minishell_data *mini, char *pwd)
{
	int		i;

	i = 0;
	if (ft_in_envp(mini->envp, "PWD"))
	{
		while (mini->envp[i] != NULL && ft_strncmp(mini->envp[i],
				"PWD", 3) != 0)
			i++;
		null_check_free_str(mini->envp[i]);
		mini->envp[i] = NULL;
		mini->envp[i] = ft_strjoin("PWD=", pwd);
		null_check_free_str(pwd);
	}
	else
	{
		while (mini->envp[i] != NULL && ft_strncmp(mini->envp[i],
				"PWD", 3) != 0)
			i++;
		null_check_free_str(mini->envp[i]);
		mini->envp[i] = NULL;
		mini->envp[i] = ft_strjoin("PWD=", pwd);
		mini->envp[i + 1] = NULL;
		null_check_free_str(pwd);
	}
}

int	ft_cd_minus_envp(char **envp, char *var)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& envp[i][ft_strlen(var)] == '=')
			return (i);
	}
	return (0);
}

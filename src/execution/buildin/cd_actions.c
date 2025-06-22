/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:47:00 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/11 21:36:09 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_cd_tilda_path(t_minishell_data *mini)
{
	char	*temp;
	char	*cwd;
	char	*path;
	char	*home;

	home = NULL;
	cwd = getcwd(NULL, 0);
	home = ft_cd_create_home(mini, home);
	temp = ft_cd_remove_tilda(mini->cmds->args[1]);
	path = ft_strjoin(home, temp);
	if (access(path, F_OK | X_OK) == 0)
	{
		ft_cd_update_old_env(mini, cwd);
		chdir(path);
		ft_cd_new_pwd(mini, path);
		null_check_free_str(temp);
		mini->exit_cd = 0;
	}
	else
	{
		null_check_free_str(temp);
		null_check_free_str(cwd);
		null_check_free_str(path);
		error_print_two_message("cd: ", mini->cmds->args[1], 2, mini);
	}
}

void	ft_cd_back(t_minishell_data *mini)
{
	char	*cwd;
	char	*furture_wd;
	int		furture_wd_size;
	int		i;

	cwd = getcwd(NULL, 0);
	furture_wd_size = ft_cd_back_size(cwd);
	furture_wd = malloc(furture_wd_size + 1);
	i = -1;
	while (++i < furture_wd_size)
		furture_wd[i] = cwd[i];
	furture_wd[i] = '\0';
	ft_cd_update_old_env(mini, cwd);
	chdir(furture_wd);
	mini->exit_cd = 0;
}

void	ft_cd_relative(t_minishell_data *mini)
{
	char	*temp;
	char	*cwd;
	char	*furture_wd;

	cwd = getcwd(NULL, 0);
	temp = ft_strjoin(cwd, "/");
	furture_wd = ft_strjoin(temp, mini->cmds->args[1]);
	if (access(furture_wd, F_OK | X_OK) == 0)
	{
		ft_cd_update_old_env(mini, cwd);
		chdir(furture_wd);
		mini->exit_cd = 0;
	}
	else
	{
		null_check_free_str(cwd);
		null_check_free_str(furture_wd);
		error_print_two_message("cd: ", mini->cmds->args[1], 2, mini);
	}
}

void	ft_cd_absolute(t_minishell_data *mini)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (access(mini->cmds->args[1], F_OK | X_OK) == 0)
	{
		ft_cd_update_old_env(mini, cwd);
		chdir(mini->cmds->args[1]);
		mini->exit_cd = 0;
	}
	else
	{
		null_check_free_str(cwd);
		error_print_two_message("cd: ", mini->cmds->args[1], 2, mini);
	}
}

void	ft_cd_home(t_minishell_data *mini)
{
	char	*future_wd;
	char	*cwd;

	if (!ft_in_envp(mini->envp, "HOME") && mini->cmds->args[1] == NULL)
	{
		error_print_one_message("cd", 4, mini);
		return ;
	}
	future_wd = NULL;
	cwd = getcwd(NULL, 0);
	future_wd = ft_cd_create_home(mini, future_wd);
	if (ft_strlen(mini->cmds->args[0]) == 2)
	{
		ft_cd_update_old_env(mini, cwd);
		chdir(future_wd);
		mini->exit_cd = 0;
	}
	else
	{
		null_check_free_str(cwd);
		null_check_free_str(future_wd);
		error_print_one_message(mini->cmds->args[0], 1, mini);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:03:35 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/13 01:14:45 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_cd_create_home(t_minishell_data *mini, char *future_wd)
{
	char	*home;
	int		i;
	int		j;

	(void)mini;
	home = getenv("HOME=");
	i = ft_strlen(home);
	while (i > -1 && home[i] != '=')
		i--;
	future_wd = malloc(ft_strlen(home) - i);
	j = -1;
	while (home[++i] != '\0')
		future_wd[++j] = home[i];
	future_wd[++j] = '\0';
	return (future_wd);
}

void	ft_cd_minus(t_minishell_data *mini)
{
	char	*oldpwd;
	char	*cwd;

	if (!ft_cd_minus_envp(mini->envp, "OLDPWD"))
		return (error_print_message(mini->cmds->args[0], NULL, 3, mini));
	cwd = getcwd(NULL, 0);
	oldpwd = ft_getenv(mini, "OLDPWD=");
	oldpwd = ft_trim_path(oldpwd);
	ft_cd_update_old_env(mini, cwd);
	chdir(oldpwd);
	ft_cd_new_pwd(mini, oldpwd);
	ft_putendl_fd(oldpwd, mini->out_fd);
	mini->exit_cd = 0;
}

void	ft_cd(t_minishell_data *mini)
{
	if (ft_strncmp(mini->cmds->args[0], "cd", 3) != 0)
		error_print_one_message(mini->cmds->args[0], 1, mini);
	else if (mini->cmds->args[1] && ((ft_strncmp(mini->cmds->args[1], "..",
					2) == 0 && ft_strlen(mini->cmds->args[1]) == 2)))
		return (ft_cd_back(mini), ft_cd_new_pwd(mini, getcwd(NULL, 0)));
	else if (mini->cmds->args[1] && ft_strncmp(mini->cmds->args[1], "-",
			1) == 0)
		return (ft_cd_minus(mini));
	else if (!mini->cmds->args[1] || ft_strncmp(mini->cmds->args[1], "~",
			2) == 0 || ft_strncmp(mini->cmds->args[1], ";", 2) == 0)
		return (ft_cd_home(mini), ft_cd_new_pwd(mini, getcwd(NULL, 0)));
	else if (mini->cmds->args[1] && ft_strncmp(mini->cmds->args[1], "~/",
			2) == 0)
		return (ft_cd_tilda_path(mini), ft_cd_new_pwd(mini, getcwd(NULL, 0)));
	else if (mini->cmds->args[1] && ft_strncmp(mini->cmds->args[1], "/",
			1) == 0)
		return (ft_cd_absolute(mini), ft_cd_new_pwd(mini, getcwd(NULL, 0)));
	else if (mini->cmds->args[1] && ft_strncmp(mini->cmds->args[1], "/Users/",
			7) != 0)
		return (ft_cd_relative(mini), ft_cd_new_pwd(mini, getcwd(NULL, 0)));
	else
		error_print_two_message("cd: ", mini->cmds->args[1], 2, mini);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:03:45 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/12 19:16:50 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_export_no_args_print(t_minishell_data *mini, char **alpha_order,
		int i, int c)
{
	int	j;

	if (c == 1)
	{
		ft_putstr_fd("declare -x ", mini->out_fd);
		j = -1;
		while (alpha_order[i][++j] != '\0' && alpha_order[i][j] != '=')
			ft_putchar_fd(alpha_order[i][j], mini->out_fd);
		ft_putstr_fd("=\"", mini->out_fd);
		while (alpha_order[i][++j] != '\0')
			ft_putchar_fd(alpha_order[i][j], mini->out_fd);
		ft_putstr_fd("\"\n", mini->out_fd);
	}
	else if (c == 2)
	{
		if (ft_strncmp(alpha_order[i], "OLDPWD", 7) != 0)
		{
			ft_putstr_fd("declare -x ", mini->out_fd);
			ft_putstr_fd(alpha_order[i], mini->out_fd);
			ft_putstr_fd("\n", mini->out_fd);
		}
	}
}

void	ft_export_no_args(t_minishell_data *mini)
{
	char	**alpha_order;
	int		i;

	alpha_order = malloc((check_envp_len(mini->envp) + 1) * sizeof(char *));
	alpha_order = ft_export_alpha(mini->envp, alpha_order);
	i = check_envp_len(alpha_order);
	while (--i > -1)
	{
		if (ft_strchr(alpha_order[i], '=') != NULL && ft_strlen(alpha_order[i] \
		) != 0)
			ft_export_no_args_print(mini, alpha_order, i, 1);
		else if (ft_strlen(alpha_order[i]) != 0)
			ft_export_no_args_print(mini, alpha_order, i, 2);
	}
	free_2d(alpha_order);
}

void	ft_realloc_do(t_minishell_data *mini, char *var, int *i, int j)
{
	if (!ft_in_envp(mini->envp, var))
	{
		if (ft_strnstr(mini->cmds->args[j], "+=",
				ft_strlen(mini->cmds->args[j])) != NULL)
			ft_export_add_plus_minus(mini->envp, *i, mini->cmds->args[j]);
		else
			mini->envp[(*i)] = ft_strdup(mini->cmds->args[j]);
		(*i)++;
		mini->envp[(*i)] = NULL;
	}
	else
	{
		if (!ft_strchr(mini->envp[ft_in_envp(mini->envp, var)], '=')
			&& (ft_strchr(mini->cmds->args[j],
					'=') > ft_strchr(mini->cmds->args[j], '+')))
			ft_export_append_ex(mini->envp, -1, mini->cmds->args[j], var);
		else if (ft_strchr(mini->cmds->args[j], '=')
			&& ft_strchr(mini->cmds->args[j], '+')
			&& (ft_strchr(mini->cmds->args[j],
					'=') > ft_strchr(mini->cmds->args[j], '+')))
			ft_export_append(mini->envp, -1, mini->cmds->args[j], var);
		else if (has_value_after_equal(mini->cmds->args[j]) != 0)
			ft_export_replace(mini->envp, mini->cmds->args[j], var);
	}
}

void	ft_realloc_size(t_minishell_data *mini, int i, int j)
{
	char	**new_envp;
	int		new_envp_size;
	char	*var;

	new_envp_size = check_envp_len(mini->envp)
		+ check_envp_len(mini->cmds->args);
	new_envp = ft_calloc((new_envp_size), sizeof(char *));
	while (mini->envp[++i] != NULL)
		new_envp[i] = ft_strdup(mini->envp[i]);
	free_2d(mini->envp);
	mini->envp = ft_calloc((new_envp_size), sizeof(char *));
	i = -1;
	while (new_envp[++i] != NULL)
		mini->envp[i] = ft_strdup(new_envp[i]);
	mini->envp[new_envp_size] = NULL;
	free_2d(new_envp);
	while (mini->cmds->args[++j] != NULL)
	{
		if (ft_export_error(mini, j) == 0)
			continue ;
		var = ft_get_env_var(mini->cmds->args[j]);
		ft_realloc_do(mini, var, &i, j);
		null_check_free_str(var);
	}
}

void	ft_export(t_minishell_data *mini)
{
	if (ft_strncmp(mini->cmds->args[0], "export", 7) != 0)
		error_print_one_message(mini->cmds->args[0], 1, mini);
	else if (mini->cmds->args[1] == NULL && ft_strlen(mini->cmds->args[0]) == 6)
	{
		ft_export_no_args(mini);
		return ;
	}
	ft_realloc_size(mini, -1, 0);
	mini->exit_cd = ft_export_exit_calc(mini);
}

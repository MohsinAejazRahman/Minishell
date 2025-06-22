/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:41:40 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/12 18:12:52 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**ft_export_alpha(char **envp, char **alpha_order)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (envp[++i] != NULL)
		alpha_order[i] = strdup(envp[i]);
	alpha_order[i] = NULL;
	i = -1;
	while (alpha_order[++i] != NULL)
	{
		j = -1;
		while (alpha_order[++j + 1] != NULL)
		{
			if (ft_strncmp(alpha_order[j], alpha_order[j + 1]
					, ft_strlen(alpha_order[j + 1])) < 0)
			{
				temp = alpha_order[j];
				alpha_order[j] = alpha_order[j + 1];
				alpha_order[j + 1] = temp;
			}
		}
	}
	return (alpha_order);
}

int	ft_export_exit_calc(t_minishell_data *mini)
{
	int	i;

	if (mini->cmds->args[1][0] == '-')
		return (2);
	i = 0;
	while (mini->cmds->args[++i] != NULL)
	{
		if (ft_isdigit(mini->cmds->args[i][0]) == 1)
			return (1);
		else if (!ft_expport_str_check(mini->cmds->args[i]))
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 07:33:32 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/10 00:53:47 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_getenv_set(char **envp, char *to_get)
{
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], to_get,
			ft_strlen(to_get)) != 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	return (1);
}

char	*ft_getenv(t_minishell_data *mini, char *to_get)
{
	char	*env;
	int		i;

	i = 0;
	while (mini->envp[i] != NULL && ft_strncmp(mini->envp[i], to_get,
			ft_strlen(to_get)) != 0)
		i++;
	if (mini->envp[i] == NULL)
		return (NULL);
	env = ft_strdup(mini->envp[i]);
	return (env);
}

void	find_and_replace_env(char **envp, char *to_find, char *to_replace)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], to_find, ft_strlen(to_find)) == 0)
		{
			null_check_free_str(envp[i]);
			envp[i] = ft_strdup(to_replace);
			break ;
		}
	}
}

char	*get_value_after_equal(char *env)
{
	int		i;
	char	*value;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] != '=')
		i++;
	value = ft_strdup(env + i + 1);
	null_check_free_str(env);
	return (value);
}

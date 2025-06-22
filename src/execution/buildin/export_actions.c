/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:55:55 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/09 21:12:14 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_export_replace(char **envp, char *replace, char *var)
{
	int	i;

	i = ft_in_envp(envp, var);
	null_check_free_str(envp[i]);
	envp[i] = NULL;
	envp[i] = ft_strdup(replace);
}

int	ft_export_append_str(char *s)
{
	int	j;
	int	k;

	j = 0;
	while (s[j] != '\0' && s[j] != '=')
		j++;
	k = 0;
	while (s[++j] != '\0')
		k++;
	return (k);
}

void	ft_export_append(char **envp, int i, char *to_add, char *var)
{
	char	*result;
	int		j;
	int		k;

	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			break ;
	result = ft_calloc(ft_strlen(envp[i]) + ft_export_append_str(to_add) + 1,
			1);
	k = -1;
	j = -1;
	while (envp[i][++j] != '\0')
		result[++k] = envp[i][j];
	j = 0;
	while (to_add[j] != '\0' && to_add[j] != '=')
		j++;
	while (to_add[++j] != '\0')
		result[++k] = to_add[j];
	result[++k] = '\0';
	null_check_free_str(envp[i]);
	envp[i] = NULL;
	envp[i] = result;
}

void	ft_export_add_plus_minus(char **envp, int i, char *to_add)
{
	char	*result;
	int		j;
	int		k;

	j = -1;
	k = -1;
	result = malloc(ft_strlen(to_add));
	while (to_add[++j] != '\0')
		if (to_add[j] != '+')
			result[++k] = to_add[j];
	result[++k] = '\0';
	envp[i] = result;
}

void	ft_export_append_ex(char **envp, int i, char *to_add, char *var)
{
	char	*result;
	int		j;
	int		k;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			break ;
	result = ft_calloc(ft_strlen(envp[i]) + ft_export_append_str(to_add) + 2,
			1);
	k = -1;
	j = -1;
	while (tmp[++j] != '\0')
		result[++k] = tmp[j];
	j = 0;
	while (to_add[j] != '\0' && to_add[j] != '=')
		j++;
	while (to_add[++j] != '\0')
		result[++k] = to_add[j];
	result[++k] = '\0';
	null_check_free_str(envp[i]);
	envp[i] = NULL;
	envp[i] = result;
	null_check_free_str(tmp);
}

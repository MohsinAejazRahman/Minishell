/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:11:40 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/11 21:41:40 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_ok_parsing(t_minishell_data *mini_dto)
{
	if (!passed_lexical_analysis(mini_dto)
		|| !passed_syntactical_analysis(mini_dto)
		|| !passed_ast_cmds_generation(mini_dto)
		|| !passed_redirections_process(mini_dto)
		|| !passed_expansion_process(mini_dto))
		return (0);
	return (1);
}

void	unshift_element(char **args, int *pos)
{
	int	j;
	int	i;

	j = -1;
	i = *pos - 1;
	while (*(args + ++j))
		;
	if (*(args + *pos))
		null_check_free_str(*(args + *pos));
	while (++i < j - 1)
		*(args + i) = *(args + i + 1);
	*(args + j - 1) = NULL;
	(*pos)--;
}

char	*get_env_value(char **envp, char *env_var)
{
	int	len;
	int	i;

	len = ft_strlen(env_var);
	i = 0;
	while (envp && (envp + i) && *(envp + i))
	{
		if (ft_strncmp(*(envp + i), env_var, len) == 0 && *(*(envp + i)
				+ len) == '=')
			return (ft_substr((*(envp + i) + len + 1), 0, ft_strlen((*(envp + i)
							+ len + 1))));
		i++;
	}
	return (NULL);
}

int	file_type_check(char *path)
{
	struct stat	is_dir;

	if (stat(path, &is_dir) == 0)
	{
		if (S_ISDIR(is_dir.st_mode))
		{
			ft_putstr_fd("minishell ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

int	file_permission_check(char *path)
{
	struct stat	is_dir;

	if (stat(path, &is_dir) == 0)
	{
		if (access(path, R_OK) == -1)
		{
			ft_putstr_fd("minishell", STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

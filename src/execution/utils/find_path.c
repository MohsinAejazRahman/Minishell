/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:59:28 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/11 21:39:56 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*init_string(t_minishell_data *mini, char *s)
{
	char	*result;

	result = ft_strdup(s);
	if (access(result, F_OK | X_OK) == 0)
		return (result);
	error_print_one_message(mini->cmds->args[0], 2, mini);
	return (free(result), NULL);
}

char	*init_path(t_minishell_data *mini, char *s)
{
	char	*result;
	char	*temp;
	char	*temp_input_path;
	int		i;

	temp = getcwd(NULL, 0);
	temp_input_path = malloc(ft_strlen(s));
	i = 0;
	while (s[++i] != '\0')
		temp_input_path[i - 1] = s[i];
	temp_input_path[i - 1] = '\0';
	result = ft_strjoin(temp, temp_input_path);
	free(temp);
	free(temp_input_path);
	if (access(result, F_OK | X_OK) == 0)
		return (result);
	error_print_one_message(mini->cmds->args[0], 2, mini);
	return (free(result), NULL);
}

char	*ft_create_path(char *path, char *command)
{
	char	*path_return;
	int		i;
	int		j;

	path_return = malloc(ft_strlen(path) + ft_strlen(command) + 1);
	if (!path_return)
		return (perror("Moh MAlloc fail in ft_create_path"), NULL);
	i = -1;
	while (path[++i] != '\0')
		path_return[i] = path[i];
	j = -1;
	while (command[++j] != '\0')
		path_return[i++] = command[j];
	path_return[i] = '\0';
	null_check_free_str(path);
	return (path_return);
}

char	*ft_trim_path(char *path)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (path[i] != '\0' && path[i] != '=')
		i++;
	temp = malloc((ft_strlen(path) - i) + 1);
	if (!temp)
		perror("find_path.c line 46");
	j = 0;
	i++;
	while (path[i] != '\0')
		temp[j++] = path[i++];
	temp[j] = '\0';
	null_check_free_str(path);
	return (temp);
}

char	*ft_find_path(t_minishell_data *mini, char *arg, int i)
{
	char	*path_s;
	char	**path_2d;
	char	*command;

	if (arg[0] == '/')
		return (init_string(mini, arg));
	if (arg[0] == '.' && arg[1] == '/' && arg[1] != '\0')
		return (init_path(mini, arg));
	path_s = ft_getenv(mini, "PATH");
	if (!path_s)
		return (null_check_free_str(path_s),
			error_print_one_message(mini->cmds->args[0], 2, mini), NULL);
	path_2d = ft_split(path_s, ':');
	null_check_free_str(path_s);
	path_2d[0] = ft_trim_path(path_2d[0]);
	command = ft_strjoin("/", arg);
	i = -1;
	while (path_2d[++i] != NULL)
	{
		path_s = ft_strjoin(path_2d[i], command);
		if (access(path_s, F_OK | X_OK) == 0)
			return (null_check_free_str(command), free_2d(path_2d), path_s);
		null_check_free_str(path_s);
	}
	return (null_check_free_str(command), free_2d(path_2d), arg);
}

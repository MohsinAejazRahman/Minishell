/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_terminal_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:11:24 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/09 21:15:56 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_user(char *envp[])
{
	while (ft_strnstr(*envp, "USER", 4) == NULL)
		envp++;
	return (*envp + 5);
}

char	*get_terminal_name_formated(char *envp[])
{
	t_hostname	hostname_arg;
	char		*username;
	char		*hostname;
	char		*pwd;

	(void)envp;
	init_hostname(&hostname_arg, "/bin/hostname");
	get_hostname_child_process(&hostname_arg);
	hostname = ft_strdup(hostname_arg.res);
	free_hostname(&hostname_arg);
	init_hostname(&hostname_arg, "/bin/pwd");
	get_hostname_child_process(&hostname_arg);
	pwd = ft_strdup(hostname_arg.res);
	free_hostname(&hostname_arg);
	username = ft_strdup(getenv("USER"));
	return (get_formated(username, hostname, pwd));
}

void	get_hostname_child_process(t_hostname *t_hostname)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("Pipe error"));
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (execve(t_hostname->cmd_args[0], t_hostname->cmd_args, NULL) == -1)
			return (perror("exceve error"));
	}
	else
	{
		wait(NULL);
		close(pipefd[1]);
		read(pipefd[0], t_hostname->res, BUFFER_SIZE);
		close(pipefd[0]);
		dup2(1, STDOUT_FILENO);
	}
}

void	init_hostname(t_hostname *hostname, char *str)
{
	hostname->cmd_args = malloc(sizeof(char *) * 2);
	hostname->cmd_args[0] = ft_strdup(str);
	hostname->cmd_args[1] = NULL;
	hostname->res = malloc(sizeof(char) * BUFFER_SIZE);
}

char	*get_formated(char *user, char *host, char *pwd)
{
	char	*hostname;
	char	*pwd_name;
	char	*curr_pwd;
	char	**process;
	char	*res;

	process = ft_split(host, '.');
	hostname = ft_strdup(process[0]);
	free_2d(process);
	curr_pwd = ft_strdup(ft_strrchr(pwd, '/') + 1);
	if (ft_strchr(curr_pwd, '\n'))
		pwd_name = ft_substr(curr_pwd, 0, ft_strlen(curr_pwd) - 1);
	else
		pwd_name = ft_strdup(curr_pwd);
	null_check_free_str(pwd);
	null_check_free_str(curr_pwd);
	res = ft_strdup(hostname);
	null_check_free_str(hostname);
	res = ft_strjoin(res, ":");
	res = ft_strjoin(res, pwd_name);
	null_check_free_str(curr_pwd);
	res = ft_strjoin(res, " ");
	res = ft_strjoin(res, user);
	return (null_check_free_str(user), null_check_free_str(pwd_name),
		res = ft_strjoin(res, "$ "), res);
}

/*
just a try to make it, it has leaks may be in the
future will fix it and make it completely works
for now i don't want to use it
*/

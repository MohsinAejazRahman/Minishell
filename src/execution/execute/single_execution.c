/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:50:57 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/13 05:00:42 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	stop(char *message)
{
	perror(message);
	exit(1);
}

int	ft_lstsize_commands(t_ast *lst)
{
	t_ast	*temp;
	int		i;

	i = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_execve(char *path, t_minishell_data *mini, int *fd)
{
	if (execve(path, mini->cmds->args, mini->envp) == -1)
	{
		error_print_one_message(mini->cmds->args[0], 1, mini);
		null_check_free_str(path);
		mini->exit_cd = 127;
		free_mini_dto(mini);
		exit(mini->exit_cd);
	}
	(void)fd;
	free_mini_dto(mini);
	exit(EXIT_SUCCESS);
}

void	parent_process_single(t_minishell_data *mini, int pid, char *path,
		int *fd)
{
	int	status;

	(void)fd;
	reset_in_and_out_single(mini, 0);
	waitpid(pid, &status, 0);
	if WIFEXITED (status)
		mini->exit_cd = WEXITSTATUS(status);
	if WIFSIGNALED (status)
		mini->exit_cd = WTERMSIG(status) + 128;
	null_check_free_str(path);
	g_global_sig = 0;
}

void	single_execution(t_minishell_data *mini)
{
	char	*path;
	int		pid;

	g_global_sig = 1;
	signal_handler_init(mini);
	mini->fds = set_fd(mini, 2, 0);
	manage_fd_single_exec(mini, 1);
	if (buildin_manager_check(mini))
		return (buildin_manager(mini), reset_in_and_out_single(mini, 0));
	path = ft_find_path(mini, mini->cmds->args[0], 0);
	if (!path)
		return ;
	pid = fork();
	if (pid == -1)
		stop("single exec fork() fail");
	else if (pid == 0)
		ft_execve(path, mini, NULL);
	parent_process_single(mini, pid, path, NULL);
	signal_handler_end(mini);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:50:57 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/13 05:05:35 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_execve_child(t_minishell_data *mini, char *path, int i, int lst_size)
{
	manage_files(mini, i, lst_size);
	if (buildin_manager_check(mini))
	{
		buildin_manager(mini);
		exit(EXIT_SUCCESS);
	}
	if (execve(path, mini->cmds->args, mini->envp) == -1)
	{
		null_check_free_str(path);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->cmds->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("command not found", 2);
		exit(127);
	}
	free_mini_dto(mini);
	exit(EXIT_SUCCESS);
}

void	child_process_multi(t_minishell_data *mini, int i, int lst_size)
{
	char	*path;

	path = NULL;
	if (!buildin_manager_check(mini))
	{
		path = ft_find_path(mini, mini->cmds->args[0], 0);
		if (!path)
			return ;
	}
	ft_execve_child(mini, path, i, lst_size);
}

void	multiple_execution(t_minishell_data *mini)
{
	int		i;
	int		lst_size;
	t_ast	*tmp;

	signal_handler_init(mini);
	lst_size = ft_lstsize_commands(mini->cmds);
	mini->fds = set_fd(mini, lst_size, 1);
	mini->pids = malloc(ft_lstsize_commands(mini->cmds) * sizeof(int));
	if (!mini->pids)
		stop("Malloc pids");
	i = -1;
	tmp = mini->cmds;
	while (mini->cmds != NULL && ++i < lst_size)
	{
		mini->pids[i] = fork();
		if (mini->pids[i] == -1)
			stop("single exec fork() fail");
		if (mini->pids[i] == 0)
			child_process_multi(mini, i, lst_size);
		mini->cmds = mini->cmds->next;
	}
	mini->cmds = tmp;
	wait_all_children(mini, lst_size);
}

void	wait_all_children(t_minishell_data *mini, int lst_size)
{
	int	i;
	int	status;

	i = -1;
	close_all_fds(mini->fds, lst_size);
	while (++i < lst_size)
	{
		waitpid(mini->pids[i], &status, 0);
		if WIFEXITED (status)
			mini->exit_cd = WEXITSTATUS(status);
		if WIFSIGNALED (status)
			mini->exit_cd = WTERMSIG(status) + 128;
	}
	free(mini->pids);
	free_fd(mini->fds, lst_size);
	g_global_sig = 0;
	signal_handler_end(mini);
}

void	close_all_fds(int **fd, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

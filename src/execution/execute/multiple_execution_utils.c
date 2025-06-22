/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_execution_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:49:18 by mohrahma          #+#    #+#             */
/*   Updated: 2024/06/13 05:06:42 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	**set_fd(t_minishell_data *mini, int lst_size, int flag)
{
	int	i;

	mini->fds = malloc(lst_size * sizeof(int *));
	if (!mini->fds)
		stop("Malloc fd");
	i = -1;
	while (++i < lst_size)
	{
		mini->fds[i] = malloc(2 * sizeof(int));
		if (!mini->fds[i])
			stop("Malloc fd[i]");
		if (flag)
			if (pipe(mini->fds[i]) < 0)
				stop("Pipe");
	}
	if (!flag)
	{
		mini->fds[0][0] = dup(STDIN_FILENO);
		mini->fds[0][1] = dup(STDOUT_FILENO);
		mini->fds[1][0] = mini->cmds->fd_infile;
		mini->fds[1][1] = mini->cmds->fd_outfile;
	}
	return (mini->fds);
}

void	free_fd(int **fd, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (fd[i])
			free(fd[i]);
	}
	free(fd);
}

void	reset_in_and_out(t_minishell_data *mini, int size)
{
	close_all_fds(mini->fds, size);
	if (mini->cmds->fd_infile != STDIN_FILENO)
	{
		if (dup2(mini->cmds->fd_infile, STDIN_FILENO) == -1)
			stop("Dup 5");
		close(mini->cmds->fd_infile);
	}
	if (mini->cmds->fd_outfile != STDOUT_FILENO)
	{
		if (dup2(mini->cmds->fd_outfile, STDOUT_FILENO) == -1)
			stop("Dup 6");
		close(mini->cmds->fd_outfile);
	}
}

void	manage_files(t_minishell_data *mini, int i, int lst_size)
{
	if (i == 0)
	{
		if (dup2(mini->fds[i][1], STDOUT_FILENO) == -1)
			stop("Dup 1");
	}
	else if (mini->cmds->next == NULL)
	{
		if (dup2(mini->fds[i - 1][0], STDIN_FILENO) == -1)
			stop("Dup 2");
	}
	else
	{
		if (dup2(mini->fds[i - 1][0], STDIN_FILENO) == -1)
			stop("Dup 3");
		if (dup2(mini->fds[i][1], STDOUT_FILENO) == -1)
			stop("Dup 4");
	}
	reset_in_and_out(mini, lst_size);
}

void	manage_fd_single_exec(t_minishell_data *mini, int i)
{
	if (mini->cmds->fd_infile != STDIN_FILENO)
	{
		if (dup2(mini->fds[i][0], STDIN_FILENO) == -1)
			stop("Dup 7");
		close(mini->cmds->fd_infile);
	}
	if (mini->cmds->fd_outfile != STDOUT_FILENO)
	{
		if (dup2(mini->fds[i][1], STDOUT_FILENO) == -1)
			stop("Dup 8");
		close(mini->cmds->fd_outfile);
	}
}

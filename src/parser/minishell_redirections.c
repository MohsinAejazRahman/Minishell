/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:11:03 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/11 20:43:20 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	passed_redirections_process(t_minishell_data *mini_dto)
{
	int		i;
	t_ast	*head_cmds;

	head_cmds = mini_dto->cmds;
	while (head_cmds)
	{
		i = -1;
		while (head_cmds && (head_cmds->args + ++i) && *(head_cmds->args + i))
		{
			if (ft_strchr(*(head_cmds->args + i), '>')
				&& ft_strlen(*(head_cmds->args + i)) <= 2)
			{
				if (!manage_out_append_to_file(head_cmds, &i))
					return (mini_dto->exit_cd = 1, 0);
			}
			else if (ft_strchr(*(head_cmds->args + i), '<')
				&& ft_strlen(*(head_cmds->args + i)) <= 2)
				if (!manage_heredoc_in_from_file(head_cmds, mini_dto, &i))
					return (0);
		}
		head_cmds = head_cmds->next;
	}
	return (1);
}

int	manage_out_append_to_file(t_ast *head_cmds, int *i)
{
	if (head_cmds->fd_outfile != STDOUT_FILENO)
		close(head_cmds->fd_outfile);
	if (ft_strncmp(*(head_cmds->args + *i), ">", 2) == 0)
		head_cmds->fd_outfile = open(*(head_cmds->args + *i + 1),
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ft_strncmp(*(head_cmds->args + *i), ">>", 2) == 0)
		head_cmds->fd_outfile = open(*(head_cmds->args + *i + 1),
				O_CREAT | O_RDWR | O_APPEND, 0644);
	if (head_cmds->fd_outfile == -1)
		return (ft_putstr_fd(TERMINAL_NAME, STDERR_FILENO), 0);
	return (unshift_n_element(head_cmds->args, i, 2), 1);
}

int	manage_heredoc_in_from_file(t_ast *head_cmds, t_minishell_data *mini_dto,
		int *i)
{
	int	j;

	j = 0;
	if (file_permission_check(*(head_cmds->args + *i + 1)) == 0)
		return (mini_dto->exit_cd = 1, 0);
	else if (file_type_check(*(head_cmds->args + *i + 1)) == 0)
		return (mini_dto->exit_cd = 126, 0);
	if (head_cmds->fd_infile != STDIN_FILENO)
		close(head_cmds->fd_infile);
	if (ft_strncmp(*(head_cmds->args + *i), "<", 2) == 0)
		head_cmds->fd_infile = open(*(head_cmds->args + *i + 1), O_RDONLY);
	if (ft_strncmp(*(head_cmds->args + *i), "<<", 2) == 0)
		head_cmds->fd_infile = manage_heredoc(head_cmds->fd_infile,
				*(head_cmds->args + *i + 1), mini_dto, j);
	if (head_cmds->fd_infile == -1)
		return (ft_putstr_fd(TERMINAL_NAME, STDERR_FILENO),
			mini_dto->exit_cd = 1, 0);
	return (unshift_n_element(head_cmds->args, i, 2), 1);
}

void	unshift_n_element(char **args, int *pos, int n)
{
	int	j;
	int	i;
	int	k;

	j = -1;
	i = *pos - 1;
	k = *pos;
	while (*(args + ++j))
		;
	while (k < *pos + n)
		null_check_free_str(*(args + k++));
	while (++i < j - n)
		*(args + i) = *(args + i + n);
	*(args + j - n) = NULL;
	(*pos)--;
}

int	manage_heredoc(int fd, char *delimiter, t_minishell_data *mini_dto, int j)
{
	char	*line;

	fd = open("obj/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_putstr_fd(TERMINAL_NAME, STDERR_FILENO), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			null_check_free_str(line);
			break ;
		}
		is_needed_expansion(mini_dto, &line, &j);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		null_check_free_str(line);
	}
	close(fd);
	fd = open("obj/heredoc", O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd(TERMINAL_NAME, STDERR_FILENO), -1);
	return (fd);
}

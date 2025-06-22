/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_syntactical_analysis.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 05:17:48 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/13 07:18:11 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	passed_syntactical_analysis(t_minishell_data *mini_dto)
{
	t_token	*head;

	head = mini_dto->tokens;
	while (head)
	{
		if (!passed_pipe_errors(head) || !passed_rediriection_error(head))
			return (mini_dto->exit_cd = 2,
				free_token_list(mini_dto->tokens), 0);
		head = head->next;
	}
	return (1);
}

int	passed_pipe_errors(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->prev || !token->next || token->prev->type == PIPE
			|| token->next->type == PIPE || token->next->type == EOL)
			return (dup2(STDERR_FILENO, STDOUT_FILENO), printf(ERR_SYNTX_MSG,
					(char)PIPE), dup2(STDOUT_FILENO, STDERR_FILENO), 0);
	}
	return (1);
}

int	passed_rediriection_error(t_token *token)
{
	if (token->type == R_DIR_IN || token->type == R_DIR_OUT
		|| token->type == R_DIR_APPEND || token->type == H_DOC)
	{
		if (token->next->type != WORD && token->next->type == EOL)
			return (dup2(STDERR_FILENO, STDOUT_FILENO),
				printf(ERR_SYNTX_MSG_RE_H, "newline"), dup2(STDOUT_FILENO,
					STDERR_FILENO), 0);
		else if (!token->prev && token->next->type != WORD)
			return (dup2(STDERR_FILENO, STDOUT_FILENO),
				printf(ERR_SYNTX_MSG_RE_H, "newline"), dup2(STDOUT_FILENO,
					STDERR_FILENO), 0);
	}
	return (1);
}

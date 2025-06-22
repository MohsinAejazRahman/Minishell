/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 02:53:00 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/09 21:19:11 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*get_next_token(t_lexer_data *l_dto)
{
	while (l_dto->pos < (int)ft_strlen(l_dto->line))
	{
		if (ft_check_space(*(l_dto->line + l_dto->pos)))
			l_dto->pos++;
		else if (*(l_dto->line + l_dto->pos) == (char)PIPE)
			return (l_dto->pos++, create_token(PIPE, NULL, NULL, NULL));
		else if (*(l_dto->line + l_dto->pos) == (char)R_DIR_IN && *(l_dto->line
				+ l_dto->pos + 1) != R_DIR_IN)
			return (l_dto->pos++, create_token(R_DIR_IN, NULL, NULL, NULL));
		else if (*(l_dto->line + l_dto->pos) == (char)R_DIR_IN && *(l_dto->line
				+ l_dto->pos + 1) == (char)R_DIR_IN)
			return (l_dto->pos += 2, create_token(H_DOC, NULL, NULL, NULL));
		else if (*(l_dto->line + l_dto->pos) == (char)R_DIR_OUT && *(l_dto->line
				+ l_dto->pos + 1) != (char)R_DIR_OUT)
			return (l_dto->pos++, create_token(R_DIR_OUT, NULL, NULL, NULL));
		else if (*(l_dto->line + l_dto->pos) == (char)R_DIR_OUT && *(l_dto->line
				+ l_dto->pos + 1) == (char)R_DIR_OUT)
			return (l_dto->pos += 2, create_token(R_DIR_APPEND, NULL, NULL,
					NULL));
		else if (!ft_check_space(*(l_dto->line + l_dto->pos)))
			return (get_token_word(l_dto));
	}
	return (create_token(EOL, NULL, NULL, NULL));
}

t_token	*create_token(t_type type, char *val, t_token *next, t_token *prev)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	res->type = type;
	if (type == PIPE)
		res->val = ft_strdup("|");
	else if (type == R_DIR_APPEND)
		res->val = ft_strdup(">>");
	else if (type == H_DOC)
		res->val = ft_strdup("<<");
	else if (type == EOL)
		res->val = ft_strdup("EOL");
	else
		res->val = val;
	res->next = next;
	res->prev = prev;
	return (res);
}

t_token	*get_token_word(t_lexer_data *lexer_dto)
{
	int		start;
	char	*word;

	start = lexer_dto->pos;
	while (*(lexer_dto->line + lexer_dto->pos))
	{
		if (*(lexer_dto->line + lexer_dto->pos) == (char)SIG_QOT
			|| *(lexer_dto->line + lexer_dto->pos) == (char)DOB_QOT)
			manage_quotes(lexer_dto);
		if (!lexer_dto->dquote && ft_check_space(*(lexer_dto->line
					+ lexer_dto->pos)) && !lexer_dto->squote)
			break ;
		if (!lexer_dto->squote && (*(lexer_dto->line
					+ lexer_dto->pos) == (char)PIPE || *(lexer_dto->line
					+ lexer_dto->pos) == (char)R_DIR_IN || *(lexer_dto->line
					+ lexer_dto->pos) == (char)R_DIR_OUT) && !lexer_dto->dquote)
			break ;
		lexer_dto->pos++;
	}
	if (lexer_dto->dquote || lexer_dto->squote)
		return (create_token(ERR, NULL, NULL, NULL));
	word = ft_calloc(sizeof(char), (size_t)(lexer_dto->pos - start + 1));
	ft_strlcpy(word, (lexer_dto->line + start), (lexer_dto->pos - start + 1));
	return (create_token(WORD, word, NULL, NULL));
}

void	manage_quotes(t_lexer_data *lexer_dto)
{
	if (*(lexer_dto->line + lexer_dto->pos) == (char)SIG_QOT
		&& *(lexer_dto->line + (lexer_dto->pos - 1)) != (char)BCK_SLH
		&& !lexer_dto->dquote && !lexer_dto->squote)
		lexer_dto->squote = 1;
	else if (*(lexer_dto->line + lexer_dto->pos) == (char)SIG_QOT
		&& *(lexer_dto->line + (lexer_dto->pos - 1)) != (char)BCK_SLH
		&& !lexer_dto->dquote && lexer_dto->squote)
		lexer_dto->squote = 0;
	else if (*(lexer_dto->line + lexer_dto->pos) == (char)DOB_QOT
		&& *(lexer_dto->line + (lexer_dto->pos - 1)) != (char)BCK_SLH
		&& !lexer_dto->dquote && !lexer_dto->squote)
		lexer_dto->dquote = 1;
	else if (*(lexer_dto->line + lexer_dto->pos) == (char)DOB_QOT
		&& *(lexer_dto->line + (lexer_dto->pos - 1)) != (char)BCK_SLH
		&& lexer_dto->dquote && !lexer_dto->squote)
		lexer_dto->dquote = 0;
}

void	free_token_list(t_token *tokens)
{
	t_token	*temp;
	t_token	*next;

	if (!tokens)
		return ;
	temp = tokens;
	while (temp)
	{
		next = temp->next;
		free(temp->val);
		free(temp);
		temp = next;
	}
	tokens = NULL;
}

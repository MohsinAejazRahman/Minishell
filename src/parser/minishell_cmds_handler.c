/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmds_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:59:28 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/01 18:23:48 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	passed_ast_cmds_generation(t_minishell_data *mini_dto)
{
	t_token	*token_head;
	t_ast	*ast_head;

	token_head = mini_dto->tokens;
	ast_head = NULL;
	while (token_head && token_head->type != EOL)
	{
		if (!token_head->prev || token_head->prev->type == PIPE)
		{
			if (!add_new_node_to_ast(&token_head, &ast_head))
				return (0);
		}
		if (token_head->type != PIPE)
		{
			if (!init_args(&token_head, &ast_head))
				return (0);
		}
		else if (token_head->type == PIPE)
			token_head = token_head->next;
	}
	mini_dto->cmds = ast_head;
	if (DEBUG)
		print_t_ast(mini_dto->cmds, "---AFTER---");
	return (1);
}

int	add_new_node_to_ast(t_token **tokens, t_ast **cmds_head)
{
	t_ast	*new_ast_node;
	t_ast	*prev_ast;
	t_token	*prev_token;

	new_ast_node = NULL;
	init_new_ast_node(&new_ast_node);
	if (!new_ast_node)
		return (0);
	if (*cmds_head)
	{
		prev_ast = *cmds_head;
		while (prev_ast && prev_ast->next)
			prev_ast = prev_ast->next;
		prev_ast->next = new_ast_node;
		new_ast_node->prev = prev_ast;
	}
	else
		*cmds_head = new_ast_node;
	prev_token = (*tokens)->prev;
	if (prev_token && prev_token->type != PIPE)
		(*tokens) = (*tokens)->next;
	return (1);
}

void	init_new_ast_node(t_ast **cmd)
{
	(*cmd) = (t_ast *)malloc(sizeof(t_ast));
	(*cmd)->args = NULL;
	(*cmd)->next = NULL;
	(*cmd)->fd_infile = STDIN_FILENO;
	(*cmd)->fd_outfile = STDOUT_FILENO;
	(*cmd)->prev = NULL;
}

int	init_args(t_token **tokens, t_ast **cmds_head)
{
	int		i;
	t_token	*head;
	t_ast	*temp;

	i = 0;
	head = *tokens;
	temp = *cmds_head;
	while (head && head->type != PIPE && head->type != EOL && ++i)
		head = head->next;
	if (!i)
		return (1);
	while (temp && (temp)->next)
		temp = (temp)->next;
	(temp)->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(temp)->args)
		return (0);
	if (!create_2d_args_null_term(tokens, &temp, i))
		return (0);
	*((temp)->args + i) = NULL;
	if (DEBUG)
		ft_printf_2d((temp)->args, "ARGS After init");
	return (1);
}

int	create_2d_args_null_term(t_token **tokens, t_ast **cmds_head, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if ((*tokens)->type == WORD)
			*((*cmds_head)->args + j) = ft_strdup((*tokens)->val);
		else
		{
			if ((*tokens)->type == R_DIR_IN)
				*((*cmds_head)->args + j) = ft_strdup("<");
			else if ((*tokens)->type == R_DIR_OUT)
				*((*cmds_head)->args + j) = ft_strdup(">");
			else if ((*tokens)->type == R_DIR_APPEND)
				*((*cmds_head)->args + j) = ft_strdup(">>");
			else if ((*tokens)->type == H_DOC)
				*((*cmds_head)->args + j) = ft_strdup("<<");
		}
		if (!*((*cmds_head)->args + j))
			return (0);
		(*tokens) = (*tokens)->next;
	}
	return (1);
}

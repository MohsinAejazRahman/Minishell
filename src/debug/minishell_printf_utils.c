/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_printf_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:29:02 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/05 20:07:28 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_printf_2d(char *str[], char *str_msg)
{
	int	i;

	i = 0;
	printf("\n%s\n", str_msg);
	while (str[i])
	{
		printf("%p [%d] ----- %s\n", (str + i), i, str[i]);
		i++;
	}
}

void	print_token(const t_token *token, char *str_msg)
{
	printf("\n%s\n", str_msg);
	if (token == NULL)
	{
		printf("Token is NULL\n");
		return ;
	}
	printf("Token:\n");
	printf("  Type: %d\n", token->type);
	printf("  Value: %s\n", token->val);
	printf("  Next: %p\n", (void *)token->next);
	printf("  Prev: %p\n", (void *)token->prev);
}

void	print_token_list(t_token *head, char *str_msg)
{
	t_token	*current;

	printf("\n%s\n", str_msg);
	current = head;
	while (current != NULL)
	{
		print_token(current, str_msg);
		current = current->next;
	}
}

void	print_t_ast(t_ast *command, char *str_msg)
{
	if (!command)
		printf("The command is NULL\n");
	while (command)
	{
		printf("Arguments:\n");
		if (command->args)
			ft_printf_2d(command->args, str_msg);
		else
			printf("  args: NULL\n");
		printf("fd_infile: %d\n", command->fd_infile);
		printf("fd_outfile: %d\n", command->fd_outfile);
		printf("Next command: %p\n", (void *)command->next);
		printf("Previous command: %p\n", (void *)command->prev);
		command = command->next;
	}
}

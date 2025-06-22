/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:56:21 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/13 02:07:16 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_mini_dto(t_minishell_data *mini_dto)
{
	if (mini_dto)
	{
		if (mini_dto->readline)
			null_check_free_str(mini_dto->readline);
		if (mini_dto->envp)
			free_2d(mini_dto->envp);
		if (mini_dto->tokens)
			free_token_list(mini_dto->tokens);
		if (mini_dto->cmds)
			free_cmd_list(mini_dto->cmds);
	}
	mini_dto = NULL;
}

void	free_cmd_list(t_ast *cmds)
{
	t_ast	*temp;

	temp = NULL;
	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
		free(temp);
	}
}

void	null_check_free_str(char *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
}

void	free_2d(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
	{
		null_check_free_str(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

void	ft_update_shell_level_set_free(t_minishell_data *mini,
		char *old_lvl_num, char *new_lvl_num)
{
	find_and_replace_env(mini->envp, "SHLVL=", old_lvl_num);
	null_check_free_str(new_lvl_num);
}

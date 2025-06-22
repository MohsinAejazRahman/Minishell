/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohrahma <mohrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 05:32:48 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/13 02:03:32 by mohrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*process_double_quotes(t_minishell_data *mini_dto, char *arg, int *i,
		char **to_expand)
{
	while (*(arg + ++(*i)) && ft_strncmp((arg + *i), "\"", 1) != 0)
	{
		if (ft_strncmp((arg + *i), "$", 1) == 0 && ft_strncmp((arg + (*i) + 1),
				" ", 1) != 0 && ft_strncmp((arg + (*i) + 1), "\"", 1) != 0)
			process_expansion(mini_dto, arg, i, to_expand);
		else
			*to_expand = ft_strncat(*to_expand, (arg + *i), 1);
	}
	return ((*i)++, *to_expand);
}

int	process_expansion(t_minishell_data *mini_dto, char *arg, int *i,
		char **to_expand)
{
	if ((arg + ++(*i)) && (ft_strncmp((arg + *i), "?", 1) == 0
			|| ft_strncmp((arg + *i), "$", 1) == 0))
	{
		if (ft_strncmp((arg + *i), "?", 1) == 0)
		{
			if (!process_exit_status(mini_dto->exit_cd, i, to_expand))
				return (0);
		}
		else if (ft_strncmp((arg + *i), "$", 1) == 0)
		{
			if (!process_exit_status(95394, i, to_expand))
				return (0);
		}
	}
	else
	{
		if (!process_env_variable(mini_dto, arg, i, to_expand))
			return ((*i)--, 0);
	}
	return (1);
}

int	process_exit_status(int exit_cod, int *i, char **to_expand)
{
	char	*exit_status;

	(*i)++;
	exit_status = ft_itoa(exit_cod);
	if (!exit_status)
		return (0);
	*to_expand = ft_strncat(*to_expand, exit_status, ft_strlen(exit_status));
	if (!*to_expand)
		return (null_check_free_str(exit_status), --(*i), 0);
	return (null_check_free_str(exit_status), --(*i), 1);
}

int	process_env_variable(t_minishell_data *mini_dto, char *arg, int *i,
		char **to_expand)
{
	char	*env_var;
	char	*env_value;
	int		start;
	int		end;

	start = *i;
	env_value = NULL;
	env_var = NULL;
	while (*(arg + *i) && ft_is_end_ch_envp(*(arg + *i)))
		(*i)++;
	end = *i;
	env_var = ft_substr(arg, start, (end - start));
	if (!env_var)
		return (0);
	env_value = get_env_value(mini_dto->envp, env_var);
	if (!env_value)
		return (null_check_free_str(env_var), 0);
	*to_expand = ft_strncat(*to_expand, env_value, ft_strlen(env_value));
	if (!*to_expand)
		return (null_check_free_str(env_var), null_check_free_str(env_value),
			--(*i), 0);
	return (null_check_free_str(env_var), null_check_free_str(env_value),
		--(*i), 1);
}

char	**concat_arrays(char **array_1, char **array_2, int start, int *flag_rf)
{
	int		length_1;
	int		length_2;
	char	**result;
	int		i;
	int		j;

	result = NULL;
	length_1 = check_envp_len(array_1);
	length_2 = check_envp_len(array_2);
	result = ft_calloc((length_1 + length_2 + 1), sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (array_1 && *(array_1 + i) && i < start)
	{
		*(result + i) = ft_strdup(*(array_1 + i));
		i++;
	}
	j = 0;
	while (array_2 && *(array_2 + j))
		*(result + i++) = ft_strdup(*(array_2 + j++));
	while (array_1 && *(array_1 + ++start))
		*(result + i++) = ft_strdup(*(array_1 + start));
	*(result + i) = NULL;
	return (free_2d(array_1), free_2d(array_2), *flag_rf = 0, result);
}

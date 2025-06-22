/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:06:12 by skhastag          #+#    #+#             */
/*   Updated: 2024/06/09 21:14:45 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	passed_expansion_process(t_minishell_data *mini_dto)
{
	t_ast	*temp_cmds;
	int		i;
	int		flag_rf;

	flag_rf = 0;
	temp_cmds = mini_dto->cmds;
	while (temp_cmds)
	{
		if (DEBUG)
			ft_printf_2d(temp_cmds->args, "before expansion");
		i = -1;
		while (temp_cmds->args && *(temp_cmds->args + ++i))
		{
			if (!is_needed_expansion(mini_dto, (temp_cmds->args + i), &flag_rf))
				unshift_element(temp_cmds->args, &i);
			if (flag_rf)
				temp_cmds->args = concat_arrays(temp_cmds->args,
						ft_split(*(temp_cmds->args + i), ' '), i, &flag_rf);
		}
		if (DEBUG)
			ft_printf_2d(temp_cmds->args, "after expansion");
		temp_cmds = temp_cmds->next;
	}
	return (1);
}

int	is_needed_expansion(t_minishell_data *mini_dto, char **args, int *flag_rf)
{
	char	*to_expand;
	char	*arg;

	to_expand = NULL;
	arg = *args;
	if (expansion_process_succeeded(mini_dto, arg, &to_expand, flag_rf))
		return (null_check_free_str(arg), *args = to_expand, 1);
	return (0);
}

char	*expansion_process_succeeded(t_minishell_data *mini_dto, char *arg,
		char **to_expand, int *flag_rf)
{
	int	i;

	i = 0;
	while (*(arg + i))
	{
		if (ft_strncmp((arg + i), "'", 1) == 0)
			process_single_quotes(arg, &i, to_expand);
		else if (ft_strncmp((arg + i), "\"", 1) == 0)
			process_double_quotes(mini_dto, arg, &i, to_expand);
		else if (ft_strncmp((arg + i), "$", 1) == 0 && *(arg + i + 1) != '\0')
		{
			if (process_expansion(mini_dto, arg, &i, to_expand))
				*flag_rf = 1;
			i++;
		}
		else
			*to_expand = ft_strncat(*to_expand, (arg + i++), 1);
	}
	return (*to_expand);
}

char	*process_single_quotes(char *arg, int *i, char **to_expand)
{
	int	start;
	int	end;

	start = ++(*i);
	if (ft_strncmp((arg + *i), "'", 1) == 0)
		return ((*i)++, NULL);
	while (*(arg + *i) && ft_strncmp((arg + *i), "'", 1) != 0)
	{
		(*i)++;
		end = *i;
	}
	(*i)++;
	*to_expand = ft_strncat(*to_expand, (arg + start), (end - start));
	return (*to_expand);
}

char	*ft_strncat(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && *(s1 + i) != '\0')
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	j = -1;
	while (++j < n && s2 && *(s2 + j) != '\0')
		*(str + i + j) = *(s2 + j);
	*(str + i + j) = '\0';
	return (null_check_free_str(s1), str);
}

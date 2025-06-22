/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhastag <skhastag@student.42heilbornn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:22:24 by skhastag          #+#    #+#             */
/*   Updated: 2024/03/10 21:15:40 by skhastag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create_new_node(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

static void	lst_clear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*next;

	if (!lst || !*lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		del(temp->content);
		free(temp);
		temp = next;
	}
	*lst = NULL;
}

static void	lst_add_to_end(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = create_new_node(new_content);
		if (!new_node)
		{
			del(new_content);
			lst_clear(&new_list, (*del));
			return (new_list);
		}
		lst_add_to_end(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

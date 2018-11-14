/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:54:00 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/14 15:56:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"



t_list  *ft_copy_list_ptr(t_list *list)
{
	t_list *res;
	t_list *current;

	res = (t_list *)malloc(sizeof(t_list));
	res = NULL;
	current = list;
	while (current != NULL)
	{
		ft_lstpushback(&res, ft_lstnew_ptr(current->content, sizeof(t_list)));
		current = current->next;
	}
	return (res);
}

void    ft_add_list_ptr(t_list **list_ptr, t_list *list) //to protect
{
	t_list *copied_list;

	copied_list = ft_copy_list_ptr(list);
	ft_lstadd(list_ptr, ft_lstnew(copied_list, sizeof(t_list)));
}

t_list  *ft_copy_list_ptr_rev(t_list *list)
{
	t_list *res;
	t_list *current;

	res = (t_list *)malloc(sizeof(t_list));
	res = NULL;
	current = list;
	while (current != NULL)
	{
		ft_lstadd(&res, ft_lstnew_ptr(current->content, sizeof(t_list)));
		current = current->next;
	}
	return (res);
}
/*
t_list  *ft_copy_list(t_list *list)
{
	t_list *res;
	t_list *current;

	res = (t_list *)malloc(sizeof(t_list));
	res = NULL;
	current = list;
	while (current != NULL)
	{
		ft_lstadd(&res, ft_lstnew(current->content, sizeof(t_list)));
		current = current->next;
	}
	return (res);
}
*/

int     ft_add_to_list_ptr(t_list **list, void *content, size_t size)
{
	t_list *node;

	if (!(node = ft_lstnew_ptr(content, size)))
		return (1);
	else
		ft_lstadd(list, node);
	return (0);
}

int     ft_add_to_list_ptr_back(t_list **list, void *content, size_t size)
{
	t_list *node;

	if (!(node = ft_lstnew_ptr(content, size)))
		return (1);
	else
		ft_lstpushback(list, node);
	return (0);
}

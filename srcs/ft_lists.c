/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:54:00 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/18 12:52:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list  *ft_copy_list_ptr_process(t_list *list)
{
	t_list *res;
	t_list *current;

	res = NULL;
	current = list;
	while (current != NULL)
	{
		if (ft_add_to_list_ptr_back(&res, current->content, sizeof(t_list)))
		{
			ft_lstdel_ptr(&res);
			return (NULL);
		}
		current = current->next;
	}
	return (res);
}

static t_list  *ft_copy_list_ptr_rev_process(t_list *list)
{
	t_list *res;
	t_list *current;

	res = NULL;
	current = list;
	while (current != NULL)
	{
		if (ft_add_to_list_ptr(&res, current->content, sizeof(t_list)))
		{
			ft_lstdel_ptr(&res);
			return (NULL);
		}
		current = current->next;
	}
	return (res);
}

int		ft_copy_list_ptr_rev(t_list *list, t_list **res)
{
	if (list)
	{
		if (!(*res = ft_copy_list_ptr_rev_process(list)))
			return (1);
	}
	else
		*res = NULL;
	return (0);
}

int		ft_copy_list_ptr(t_list *list, t_list **res)
{
	if (list)
	{
		if (!(*res = ft_copy_list_ptr_process(list)))
			return (1);
	}
	else
		*res = NULL;
	return (0);
}

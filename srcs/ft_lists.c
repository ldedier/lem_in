/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:54:00 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/17 15:50:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list  *ft_copy_list_ptr(t_list *list)
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

t_list  *ft_copy_list_ptr_rev(t_list *list)
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

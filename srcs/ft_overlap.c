/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overlap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:28:49 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:29:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_share_rooms(t_path *path1, t_path *path2)
{
	t_list	*rooms1;
	t_list	*rooms2;

	rooms1 = path1->rooms;
	while (rooms1 != NULL)
	{
		rooms2 = path2->rooms;
		while (rooms2 != NULL)
		{
			if (rooms1->content == rooms2->content)
				return (1);
			rooms2 = rooms2->next;
		}
		rooms1 = rooms1->next;
	}
	return (0);
}

int		ft_process_overlaps_path_list(t_list *ptr,
		t_list **prev, t_path *path, t_list **overlapping)
{
	t_path	*current;

	while (ptr != NULL)
	{
		current = (t_path *)(ptr->content);
		if (ft_share_rooms(current, path))
		{
			if (*overlapping || current->length <= path->length)
				return (1);
			else
				*overlapping = ptr;
		}
		if (!(*overlapping))
			*prev = ptr;
		ptr = ptr->next;
	}
	return (0);
}

int		ft_overlaps_path_list(t_list **path_list, t_path *path)
{
	t_list	*ptr;
	t_list	*overlapping;
	t_list	*prev;

	ptr = *path_list;
	overlapping = NULL;
	prev = NULL;
	if (ft_process_overlaps_path_list(ptr, &prev, path, &overlapping))
		return (1);
	if (overlapping)
	{
		if (prev == NULL)
			*path_list = (*path_list)->next;
		else
			prev->next = prev->next->next;
		free(overlapping);
	}
	return (0);
}

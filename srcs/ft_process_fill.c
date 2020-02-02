/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:01:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:58:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_add_path_from_rooms(t_list **paths, t_list *rooms, int length)
{
	t_list	*rooms_cpy;
	t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (1);
	if (ft_copy_list_ptr_rev(rooms, &rooms_cpy))
		return (1);
	path->length = length;
	path->rooms = rooms_cpy;
	path->semi_mp = NULL;
	path->mps = NULL;
	if (ft_add_to_list_ptr(paths, path, sizeof(t_path)))
		return (1);
	return (0);
}

int		ft_process_fill_end(t_list **path, t_lem *lem)
{
	int length;

	length = ft_lstlength(*path);
	if ((length < lem->paths.min_length) ||
			(lem->paths.min_length == -1))
		lem->paths.min_length = length;
	if (ft_add_path_from_rooms(&(lem->paths.paths_list), *path, length))
		return (1);
	if (*path == NULL)
		lem->paths.max_paths = 0;
	else
		lem->paths.max_paths -= 1;
	return (0);
}

int		ft_process_fill_2(t_room *room, t_lem *lem, t_list **path, int *dist)
{
	t_list	*current;

	if (room != lem->map.end)
	{
		current = room->neighbours;
		while (current != NULL)
		{
			if (ft_process_fill((t_room *)(current->content), lem, path, dist))
				return (1);
			current = current->next;
		}
		if (room != lem->map.start)
			ft_lstpop_ptr(path);
	}
	else
	{
		if (ft_process_fill_end(path, lem))
			return (1);
	}
	return (0);
}

int		ft_process_fill(t_room *room, t_lem *lem, t_list **path, int *dist)
{
	int dist_save;

	dist_save = *dist;
	if (!room->parsed && room->dist >= *dist && lem->paths.max_paths != 0)
	{
		*dist = room->dist;
		room->parsed = 1;
		if (room != lem->map.start && room != lem->map.end)
		{
			if (ft_add_to_list_ptr(path, room, sizeof(t_room)))
				return (1);
		}
		if (ft_process_fill_2(room, lem, path, dist))
			return (1);
		room->parsed = 0;
		*dist = dist_save;
	}
	return (0);
}

int		ft_fill_paths(t_lem *lem)
{
	t_list	*path;
	int		dist;

	lem->paths.max_paths = 100000000;
	path = NULL;
	dist = 0;
	ft_reset_pathfinding(&(lem->map));
	if (ft_process_fill(lem->map.start, lem, &path, &dist))
		return (1);
	return (0);
}

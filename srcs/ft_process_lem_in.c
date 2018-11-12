/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_lem_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:40:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/12 16:30:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <time.h>

void    ft_reset_pathfinding(t_map *map)
{
	t_list *ptr;

	ptr = map->rooms;
	while (ptr != NULL)
	{
		((t_room *)(ptr->content))->parsed = 0;
		ptr = ptr->next;
	}
}

t_list	*ft_copy_list_ptr(t_list *list)
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

t_list	*ft_copy_list_ptr_rev(t_list *list)
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

t_list	*ft_copy_list(t_list *list)
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

void	ft_add_path_from_rooms(t_list **paths, t_list *rooms, int length) //to protect
{
	t_list	*rooms_cpy;
	t_path	*path = (t_path *)malloc(sizeof(t_path));
	rooms_cpy = ft_copy_list_ptr_rev(rooms);
	path->length = length;
	path->rooms = rooms_cpy;
	//ft_affich_room_list(path->rooms);
	path->semi_mps = NULL;
	path->mps = NULL;
	ft_lstadd(paths, ft_lstnew_ptr(path, sizeof(t_path)));
}

void	ft_add_list_ptr(t_list **list_ptr, t_list *list) //to protect
{
	t_list *copied_list;

	copied_list = ft_copy_list_ptr(list);
	ft_lstadd(list_ptr, ft_lstnew(copied_list, sizeof(t_list)));
}

void	ft_process_fill(t_room *room, t_lem *lem, t_list **path, int *max_paths)
{
	t_list *current;
	int length;

	if (!room->parsed && *max_paths != 0)
	{
		room->parsed = 1;
		if (room != lem->map.start && room != lem->map.end)
			ft_lstadd(path, ft_lstnew_ptr(room, sizeof(t_room)));
		if (room != lem->map.end)
		{
			current = room->neighbours;
			while (current != NULL)
			{
				ft_process_fill((t_room *)(current->content), lem, path, max_paths);
				current = current->next;
			}
			if (room != lem->map.start)
				ft_lstpop(path);
		}
		else
		{
			length = ft_lstlength(*path);
			if ((length < lem->paths.min_length) ||
					(lem->paths.min_length == -1))
				lem->paths.min_length = length;
			ft_add_path_from_rooms(&(lem->paths.paths_list), *path, length);
			if (*path == NULL)
				*max_paths = 0;
			else
				*max_paths -= 1;
		}
		room->parsed = 0;
	}
}

int		ft_fill_paths(t_lem *lem)
{
	t_list	*path;
	int max_paths;

	max_paths = 10000;
	path = NULL;
	ft_reset_pathfinding(&(lem->map));
	ft_process_fill(lem->map.start, lem, &path, &max_paths);
	return (1);
}

int		ft_share_content_multi_path(t_multi_path *mpath, t_list *path)
{
	t_list *current_path;
	t_list *current;
	t_list *current2;

	current_path = mpath->paths;
	while (current_path != NULL)
	{
		current = (t_list *)(current_path->content);
		while (current != NULL)
		{
			current2 = path;
			while (current2 != NULL)
			{
				if (current->content == current2->content)
					return (1);
				current2 = current2->next;
			}
			current = current->next;
		}
		current_path = current_path->next;
	}
	return (0);
}

void	ft_add_path_to_multi_path(t_multi_path *mpath, t_list *list)
{
	ft_lstpushback(&(mpath->paths), ft_lstnew(ft_copy_list_ptr(list), sizeof(t_list)));
	mpath->path_count++;
}

t_semi_mp	*ft_new_semi_mp(size_t order, t_path *path)
{
	t_semi_mp *res;

	res = (t_semi_mp *)malloc(sizeof(t_semi_mp));
	res->order = order;
	res->path = path;
	return (res);
}

void	ft_update_matching_smps(t_path *path1, t_path *path2)
{
	t_list *current;
	t_list *current2;

	int i;
	int j;
	current = path1->rooms;
	i = 0;
	while (current != NULL)
	{
		j = 0;
		current2 = path2->rooms;
		while (current2 != NULL)
		{
			if (current->content == current2->content)
			{
				if (j > i)
				{
					ft_lstadd(&(path1->semi_mps),
							ft_lstnew_ptr(ft_new_semi_mp (j - i, path2),
								sizeof(t_semi_mp)));
					return ;
				}
			}
			current2 = current2->next;
			j++;
		}
		current = current->next;
		i++;
	}
}

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

int		ft_overlaps_path_list(t_list **path_list, t_path* path)
{
	t_list	*ptr;
	t_path	*current;
	t_list	*overlapping;
	t_list	*prev;

	ptr = *path_list;
	overlapping = NULL;
	prev = NULL;
	while (ptr != NULL)
	{
		current = (t_path *)(ptr->content);
		if (ft_share_rooms(current, path))
		{
			if (overlapping || current->length <= path->length)
				return 1;
			else
				overlapping = ptr;
		}
		if (!overlapping)
			prev = ptr;
		ptr = ptr->next;
	}
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

void	ft_add_to_mps(t_list **mps, t_path *path)
{
	if (!ft_overlaps_path_list(mps, path))
		ft_lstadd(mps, ft_lstnew_ptr(path, sizeof(t_path)));
}

void	ft_update_mps(t_path *path1, t_path *path2)
{
	t_list *current;
	t_list *current2;

	int i;
	int j;
	current = path1->rooms;
	i = 0;
	while (current != NULL)
	{
		j = 0;
		current2 = path2->rooms;
		while (current2 != NULL)
		{
			if (current->content == current2->content)
				return;
			current2 = current2->next;
			j++;
		}
		current = current->next;
		i++;
	}
	ft_add_to_mps(&(path1->mps), path2);
	ft_add_to_mps(&(path2->mps), path1);
}

int		ft_fill_mps(t_lem *lem)
{
	t_list *current;
	t_list *to_compare;

	current = lem->paths.paths_list;
	while (current != NULL)
	{
		to_compare = current->next;
		while (to_compare != NULL)
		{
			ft_update_mps((t_path *)current->content,
				(t_path *)(to_compare->content));
			to_compare = to_compare->next;
		}
		current = current->next;
	}
	return (1);
}

int		ft_is_compatible_path_to_single_path(t_path *single, t_path *path)
{
	t_list	*mps;

	if(ft_lstlength(path->mps) <= ft_lstlength(single->mps))
		return (0);
	mps = single->mps;
	while (mps != NULL)
	{
		if (ft_share_rooms(mps->content, path))
			return (0);
		mps = mps->next;
	}
	return (1);
}

int		ft_fill_matching_smps(t_lem *lem)
{
	t_list *current;
	t_list *to_compare;
	current = lem->paths.paths_list;

	while (current != NULL)
	{
		if (((t_path *)current->content)->length == lem->paths.min_length)
		{
			to_compare = lem->paths.paths_list;
			while (to_compare != NULL)
			{
				if (current != to_compare && 
						((t_path *)(to_compare->content))->mps != NULL &&
						ft_is_compatible_path_to_single_path(current->content,
							to_compare->content))
				{
					ft_update_matching_smps((t_path *)current->content,
							(t_path *)(to_compare->content));
				}
				to_compare = to_compare->next;
			}
		}
		current = current->next;
	}
	return (1);
}

int		ft_fill_metadata(t_lem *lem)
{
	ft_fill_mps(lem);
	ft_fill_matching_smps(lem);
	return (1);
}

int		ft_is_better_than(t_path *path, t_path *to_compare)
{
	return (ft_lstlength(path->mps) > ft_lstlength(to_compare->mps) 
		|| ft_lstlength(path->semi_mps) > ft_lstlength(to_compare->semi_mps));
}

t_path	*ft_chosen_path(t_lem *lem)
{
	t_list *paths;
	t_path *path;
	t_path *chosen;
	int first;

	paths = lem->paths.paths_list;
	first = 1;
	chosen = NULL;
	while (paths != NULL)
	{
		path = (t_path *)(paths->content);
		if (first == 1 || (path->length == lem->paths.min_length 
				&& ft_is_better_than(path, chosen)))
		{
			chosen = path;
			first = 0;
		}
		paths = paths->next;
	}
	return (chosen);
}

int     ft_process_lem_in(t_lem *lem)
{
	t_path *chosen;
	if (!ft_fill_paths(lem))
		return (-1);
	if (lem->verbosed)
	{
//		ft_affich_paths(lem->paths.paths_list);
//		ft_printf("end of path list\n");
	}
	if (!ft_fill_metadata(lem))
		return (-1);
	chosen = ft_chosen_path(lem);
//	ft_affich_path(chosen, 1);
//	ft_affich_paths(lem->paths.paths_list, 1);
//	ft_printf("%d\n", lem->paths.min_length);
//	if (lem->verbosed)
//	{
//		ft_affich_multi_paths(lem->paths.multipaths_list);
//	}
	return 0;
}

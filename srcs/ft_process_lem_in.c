/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_lem_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:40:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/05 13:26:20 by ldedier          ###   ########.fr       */
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

void	ft_add_list_ptr_rev(t_list **list_ptr, t_list *list) //to protect
{
	t_list	*rooms;
	t_list	*ptr;
	t_path	*path = (t_path *)malloc(sizeof(t_path));

	ptr = ft_lstnew_ptr(path, sizeof(t_path));
	rooms = ft_copy_list_ptr_rev(list);
	
	path->rooms = rooms;
	path->semi_mps = NULL;
	path->mps = NULL;
	ft_lstadd(list_ptr, ft_lstnew(ptr, sizeof(t_list)));
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

	if (!room->parsed && *max_paths != 0)
	{
		room->parsed = 1;
		if (room != lem->map.start && room != lem->map.end)
		{
			ft_lstadd(path, ft_lstnew_ptr(room, sizeof(t_room)));
		}
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
			ft_add_list_ptr_rev(&(lem->paths.paths_list), *path);
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
	max_paths = 100000;
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
				{
					return (1);
				}
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

int		ft_fill_multi_paths(t_lem *lem)
{
	t_list *current;
	t_list *to_compare;
	t_multi_path *mpath;

	current = lem->paths.paths_list;
	while (current != NULL)
	{
		mpath = (t_multi_path *)malloc(sizeof(t_multi_path));
		mpath->path_count = 1;
		mpath->paths = NULL;
		ft_lstadd(&(mpath->paths), ft_lstnew(current->content,
					sizeof(t_list)));
		ft_lstadd(&(lem->paths.multipaths_list),
				ft_lstnew_ptr(mpath, sizeof(t_multi_path)));

		to_compare = current->next;
		while (to_compare != NULL)
		{
			if (!ft_share_content_multi_path(mpath,
						(t_list *)(to_compare->content)))
			{
				ft_add_path_to_multi_path(mpath,
						(t_list *)(to_compare->content));
			}
			to_compare = to_compare->next;
		}
		current = current->next;
	}
	return (1);
}

int     ft_process_lem_in(t_lem *lem)
{
	if (!ft_fill_paths(lem))
		return (-1);
	if (lem->verbosed)
	{
		ft_affich_list_of_list(lem->paths.paths_list);
		ft_printf("end of path list\n");
	}
	if (!ft_fill_multi_paths(lem))
		return (-1);
	if (lem->verbosed)
	{
		ft_affich_multi_paths(lem->paths.multipaths_list);
	}
	return 0;
}

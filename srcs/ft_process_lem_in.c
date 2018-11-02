/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_lem_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:40:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/02 16:28:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <time.h>

/*
** find the optimal ants movement for each turn and write it on standard output
*/

void    ft_affich_room_list(t_list *room_list)
{
	t_list *ptr;

	ptr = room_list;
	t_room *room;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		ft_printf("name: %s\n", room->name);
		ptr = ptr->next;
	}
	ft_printf("\n");
}

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
		ft_lstadd(&res, ft_lstnew_ptr(current->content, sizeof(*(current->content))));
		current = current->next;
	}
	return (res);
}

void	ft_add_list_ptr(t_list **list_ptr, t_list *list) //to protect
{
	ft_lstadd(list_ptr,
			ft_lstnew_ptr(ft_copy_list_ptr(list), sizeof(t_list *)));
}

void	ft_process_fill(t_room *room, t_lem *lem, t_list **path)
{
	t_list *current;

	if (room == lem->map.end)
	{
		ft_lstadd(path, ft_lstnew_ptr(room, sizeof(t_room)));
		ft_add_list_ptr(&(lem->paths.paths_list), *path);
		ft_lstpop(path);
	}
	else if (!room->parsed)
	{
		room->parsed = 1;
		ft_lstadd(path, ft_lstnew_ptr(room, sizeof(t_room)));
		current = room->neighbours;
		while (current != NULL)
		{
			ft_process_fill((t_room *)(current->content), lem, path);
			current = current->next;
		}
		ft_lstpop(path);
		room->parsed = 0;
	}
}

void	ft_affich_list_of_list(t_list *lol)
{
	t_list *ptr;
	ptr = lol;
	while (ptr != NULL)
	{
		ft_affich_room_list((t_list *)(ptr->content));
		ptr = ptr->next;
	}
}

int	ft_fill_paths(t_lem *lem)
{
	(void)(lem);

	t_list	*path;

	path = NULL;
	ft_reset_pathfinding(&(lem->map));
	
	ft_process_fill(lem->map.start, lem, &path);
	
	ft_affich_list_of_list(lem->paths.paths_list);

	return (1);
}

int		ft_process_lem_in(t_lem *lem)
{
	if (!ft_fill_paths(lem))
		return (-1);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 13:34:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/19 12:49:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    ft_affich_room_list(t_list *room_list)
{
	t_list *ptr;

	ptr = room_list;
	t_room *room;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		ft_printf("name: %s\n", room->name);
		ft_printf("dist: %d\n", room->dist);
		ptr = ptr->next;
	}
	ft_printf("\n");
}

void    ft_affich_list_of_list(t_list *lol)
{
	t_list *ptr;

	ptr = lol;
	while (ptr != NULL)
	{
		ft_affich_room_list((t_list *)(ptr->content));
		ptr = ptr->next;
	}
}

void	ft_affich_semi_matching_path(t_semi_mp *mp, int rec)
{
	if (mp)
	{
		ft_printf("order: %d\n", mp->order);
		ft_affich_path(mp->path, rec);
		ft_printf("\n");
	}
	else
		ft_printf("none\n");
}

/*
void	ft_affich_semi_matching_paths(t_list *smps, int rec)
{
	t_list *ptr;
	t_semi_mp *smp;

	ptr = smps;
	while (ptr != NULL)
	{
		smp = (t_semi_mp *)(ptr->content);
		ft_affich_semi_matching_path(smp, rec);
		ptr = ptr->next;
	}
}
*/

void	ft_affich_path(t_path *path, int rec)
{
	t_list *rooms;
	if (path != NULL)
	{
		ft_printf("new path:\n\nrooms:\n");
		rooms = path->rooms;
		ft_printf("HEHEHE\n");
		ft_affich_room_list(path->rooms);

		if (rec)
		{
			ft_printf(RED"\nmatching paths:\n");
			ft_affich_paths(path->mps, 0);

			ft_printf(CYAN"\nsemi matching paths:\n");
			ft_affich_semi_matching_path(path->semi_mp, 1);
			ft_printf(EOC"\nend of path\n");
		}
	}
	else
		ft_printf("deleted !!\n");
}


void    ft_affich_paths(t_list *paths, int rec)
{
	t_list *ptr;
	t_path *path;

	ptr = paths;
	while (ptr != NULL)
	{
		path = (t_path *)(ptr->content);
		ft_affich_path(path, rec);
		ptr = ptr->next;
	}
}

void	ft_affich_room_lite(t_room *room)
{
	ft_printf("room name: %s\n", room->name);
}

void	ft_affich_room(t_room *room)
{
	t_list *ptr;
	ft_printf("room name: %s\n", room->name);
//	ft_printf("ants number: %d\n", room->ant_number);
	ft_printf("ants count: %d\n", room->ant_count);
	ft_printf("parsed: %d\n", room->parsed);

	int i;
	i = 1;
	ptr = room->neighbours;
	while (ptr != NULL)
	{
		ft_printf("neighbour #%d\nname: %s\n",i++, ((t_room *)(ptr->content))->name);
		ptr = ptr->next;
	}	
	ft_printf("\n");
}

void	ft_affich_map(t_map *map)
{
	t_list *ptr;

	ft_printf("begin:");
	ft_affich_room(map->start);
	ft_printf("\n");

	ft_printf("end:");
	ft_affich_room(map->end);
	ft_printf("\n");
	ptr = map->rooms; 
	while (ptr != NULL)
	{
		ft_affich_room((t_room *)(ptr->content));
		ptr = ptr->next;
	}
}

void	ft_affich_queue(t_list *queue)
{
	t_list *ptr;

	ptr = queue; 
	while (ptr != NULL)
	{
		ft_affich_room((t_room *)(ptr->content));
		ptr = ptr->next;
	}
}

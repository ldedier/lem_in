/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:00:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 15:51:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_get_room(t_list *rooms, char *str)
{
	while (rooms != NULL)
	{
		if (!ft_strcmp(((t_room *)(rooms->content))->name, str))
			return ((t_room *)(rooms->content));
		rooms = rooms->next;
	}
	return (NULL);
}

void	ft_delete_rooms(t_list **rooms)
{
	t_list	*ptr;
	t_room	*room;

	ptr = *rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		ft_lstdel_ptr(&(room->neighbours));
		ft_strdel(&(room->name));
		free(room);
		ptr = ptr->next;
	}
	ft_lstdel_ptr(rooms);
}

t_room	*ft_get_neighbour(t_room *room, char *room_name)
{
	t_list	*ptr;
	t_room	*neighbour;

	ptr = room->neighbours;
	while (ptr != NULL)
	{
		neighbour = (t_room *)(ptr->content);
		if (!ft_strcmp(neighbour->name, room_name))
			return (neighbour);
		ptr = ptr->next;
	}
	return (NULL);
}

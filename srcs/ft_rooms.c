/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:00:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/16 16:02:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    ft_delete_rooms(t_list **rooms)
{
	t_list  *ptr;
	t_room  *room;

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

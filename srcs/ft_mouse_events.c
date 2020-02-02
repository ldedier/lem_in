/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 02:51:24 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 15:41:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_select_room(t_env *e, t_room *room, int x, int y)
{
	e->selected_room = room;
	e->grab.grabbed_room = room;
	e->grab.x_diff = room->corr_x - x;
	e->grab.y_diff = room->corr_y - y;
	ft_put_to_end(e);
}

void	ft_grab_room(t_env *e, int x, int y)
{
	t_list	*ptr;
	t_room	*room;
	t_room	*roomptr;

	roomptr = NULL;
	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (x >= room->corr_x && x <= room->corr_x + e->room_size &&
				y >= room->corr_y && y <= room->corr_y + e->room_size)
			roomptr = room;
		ptr = ptr->next;
	}
	if (roomptr != NULL)
	{
		ft_select_room(e, roomptr, x, y);
		return ;
	}
	if (y > e->react.grass_border)
		e->selected_room = NULL;
}

void	ft_mouse_down(t_env *e, SDL_Event event)
{
	ft_grab_room(e, event.button.x, event.button.y);
}

void	ft_mouse_up(t_env *e, SDL_Event event)
{
	(void)event;
	e->grab.grabbed_room = NULL;
}

void	ft_mouse_motion(t_env *e, SDL_Event event)
{
	if (e->grab.grabbed_room)
	{
		e->grab.grabbed_room->corr_x = ft_clamp(0, event.motion.x
				+ e->grab.x_diff, e->dim.width - e->room_size);
		e->grab.grabbed_room->corr_y = ft_clamp(e->react.grass_border,
				event.motion.y + e->grab.y_diff, e->dim.height - e->room_size);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 02:51:24 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/16 16:50:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_reset_pos(t_env *e)
{
	t_list *ptr;
	t_room *room;

	e->grab.grabbed_room = NULL;
	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		room->corr_x = room->corr_x_init;
		room->corr_y = room->corr_y_init;
		ptr = ptr->next;
	}
}


void	ft_toggle_pause(t_env *e)
{
	if (e->anim.pause == 0)
		e->anim.pause = 1;
	else
	{
		e->anim.previous = SDL_GetTicks();
		e->anim.pause = 0;
	}
}

void	ft_key_down(t_env *e, SDL_Keycode code)
{
	if (code == SDLK_r)
		ft_reset_pos(e);
	if (code == SDLK_SPACE)
		ft_toggle_pause(e);
}

void 	ft_relink_end(t_list *node, t_list *prev)
{
	if (node != NULL)
	{
		prev->next = node;
		node->next = NULL;
	}
}

void	ft_put_to_end(t_env *e)
{
	t_list *prev;
	t_list *current;
	t_room *room;
	t_list *node;

	node = NULL;
	prev = NULL;
	current = e->lem.map.rooms;
	while (current != NULL)
	{
		room = (t_room *)(current->content);
		if (room == e->selected_room && current->next != NULL)
		{
			node = current;
			if (prev == NULL)
				e->lem.map.rooms = current->next;
			else
				prev->next = current->next;
		}
		prev = current;
		current = current->next;
	}
	ft_relink_end(node, prev);
}
	
void	ft_grab_room(t_env *e, int x, int y)
{

	t_list	*ptr;
	t_room 	*room;
	t_room	*roomptr;

	roomptr = NULL;
	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (x >= room->corr_x && x <= room->corr_x + e->room_size &&
				y >= room->corr_y && y <= room->corr_y + e->room_size)
		{
			roomptr = room;
		}
		ptr = ptr->next;
	}
	if (roomptr != NULL)
	{
		e->selected_room = roomptr;
		e->grab.grabbed_room = roomptr;
		e->grab.x_diff = roomptr->corr_x - x;
		e->grab.y_diff = roomptr->corr_y - y;
		ft_put_to_end(e);
		return;
	}
	if (y > GRASS_BORDER)
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
		e->grab.grabbed_room->corr_x = ft_clamp(0, event.motion.x + e->grab.x_diff, e->dim.width - e->room_size);
		e->grab.grabbed_room->corr_y = ft_clamp(GRASS_BORDER, event.motion.y + e->grab.y_diff, e->dim.height - e->room_size);
	}
}

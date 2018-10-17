/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 02:51:24 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/21 00:47:12 by ldedier          ###   ########.fr       */
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
	if (e->keys.can_pause)
	{
		if (e->anim.pause == 0)
			e->anim.pause = 1;
		else
		{
			e->anim.previous = SDL_GetTicks();
			e->anim.pause = 0;
		}
		e->keys.can_pause = 0;
	}
}


void	ft_key_down(t_env *e, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_RIGHT)
		e->keys.right = 1;
	if (event.key.keysym.sym == SDLK_LEFT)
		e->keys.left = 1;
	if (event.key.keysym.sym == SDLK_UP)
		e->keys.up = 1;
	if (event.key.keysym.sym == SDLK_DOWN)
		e->keys.down = 1;
	if (event.key.keysym.sym == SDLK_r)
		ft_reset_pos(e);
	if (event.key.keysym.sym == SDLK_SPACE)
		ft_toggle_pause(e);

}

void	ft_key_up(t_env *e, SDL_Event event)
{

	if (event.key.keysym.sym == SDLK_RIGHT)
		e->keys.right = 0;
	if (event.key.keysym.sym == SDLK_LEFT)
		e->keys.left = 0;
	if (event.key.keysym.sym == SDLK_UP)
		e->keys.up = 0;
	if (event.key.keysym.sym == SDLK_DOWN)
		e->keys.down = 0;
	if (event.key.keysym.sym == SDLK_SPACE)
		e->keys.can_pause = 1;
}

void	ft_grab_room(t_env *e, int x, int y)
{

	t_list *ptr;
	t_room *room;
	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (x >= room->corr_x && x <= room->corr_x + e->room_size &&
				y >= room->corr_y && y <= room->corr_y + e->room_size)
		{
			e->selected_room = room;
			e->grab.grabbed_room = room;
			e->grab.x_diff = room->corr_x - x;
			e->grab.y_diff = room->corr_y - y;
			return;
		}
		ptr = ptr->next;
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

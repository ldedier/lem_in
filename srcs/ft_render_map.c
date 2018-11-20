/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:53:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 12:53:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_render_links(t_env *e)
{
	t_list		*ptr;
	t_list		*neigh_ptr;
	t_room		*room;
	SDL_Rect	pos;

	ptr = e->lem.map.rooms;
	pos.w = e->room_size;
	pos.h = e->room_size;
	SDL_SetRenderDrawColor(e->sdl.renderer, 255, 255, 255, 255);
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		neigh_ptr = room->neighbours;
		while (neigh_ptr != NULL)
		{
			SDL_RenderDrawLine(e->sdl.renderer, room->corr_x + e->room_size / 2,
				room->corr_y + e->room_size / 2,
				((t_room *)(neigh_ptr->content))->corr_x + e->room_size / 2,
				((t_room *)(neigh_ptr->content))->corr_y + e->room_size / 2);
			neigh_ptr = neigh_ptr->next;
		}
		ptr = ptr->next;
	}
}

void		ft_render_room(t_env *e, t_room *room, SDL_Rect *pos)
{
	if (room == e->lem.map.start)
		SDL_RenderCopy(e->sdl.renderer,
				e->sdl.textures[START_SPRITE + (room == e->selected_room) * 3],
				NULL, pos);
	else if (room == e->lem.map.end)
		SDL_RenderCopy(e->sdl.renderer,
				e->sdl.textures[END_SPRITE + (room == e->selected_room) * 3],
				NULL, pos);
	else
		SDL_RenderCopy(e->sdl.renderer,
				e->sdl.textures[ROOM + (room == e->selected_room) * 3],
				NULL, pos);
}

void	ft_render_rooms(t_env *e)
{
	t_list		*ptr;
	t_room		*room;
	SDL_Rect	pos;

	ptr = e->lem.map.rooms;
	pos.w = e->room_size;
	pos.h = e->room_size;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		pos.x = room->corr_x;
		pos.y = room->corr_y;
		ft_render_room(e, room, &pos);
		ptr = ptr->next;
	}
}

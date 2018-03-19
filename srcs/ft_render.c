/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 02:30:10 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/19 04:44:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_render_links(t_env *e)
{
	t_list *ptr;
	t_list *neigh_ptr;
	t_room *room;
	SDL_Rect pos;
	ptr = e->lem.map.rooms;
	pos.w = e->room_size;
	pos.h = e->room_size;
	SDL_SetRenderDrawColor( e->sdl.renderer, 255, 255, 255, 255);
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		neigh_ptr = room->neighbours;
		while (neigh_ptr != NULL)
		{
			SDL_RenderDrawLine (e->sdl.renderer, room->corr_x + e->room_size / 2, room->corr_y + e->room_size / 2, ((t_room *)(neigh_ptr->content))->corr_x + e->room_size / 2, ((t_room *)(neigh_ptr->content))->corr_y + e->room_size / 2);
			neigh_ptr = neigh_ptr->next;
		}
		ptr = ptr->next;
	}
}

void	ft_render_rooms(t_env *e)
{
	t_list *ptr;
	t_room *room;
	SDL_Rect pos;
	ptr = e->lem.map.rooms;
	pos.w = e->room_size;
	pos.h = e->room_size;
	//SDL_Texture *circle;
	//circle = SDL_CreateTexture(e->sld.renderer, 32, access, ROOM_SIZE, ROOM_SIZE);
	//circle = SDL_CreateTexture(e->sdl.renderer, SDL_PIXELFORMAT_RGBA8888,
	//		                        SDL_TEXTUREACCESS_STREAMING, ROOM_SIZE, ROOM_SIZE);

	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);	
		pos.x = room->corr_x;
		pos.y = room->corr_y;
		if (room == e->lem.map.start)
			SDL_SetRenderDrawColor( e->sdl.renderer, 0, 0, 255, 255);
		else if (room == e->lem.map.end)
			SDL_SetRenderDrawColor( e->sdl.renderer, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor( e->sdl.renderer, 255, 255, 255, 255);
		SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[ROOM], NULL, &pos);
		ptr = ptr->next;
	}
}

/*
 ** return the position of moving ant at the very instant
 */
SDL_Rect	ft_get_pos(t_env *e, t_transition *tr)
{
	int diff;
	SDL_Rect res;

	diff =  SDL_GetTicks() - e->anim.start;
	res.w = e->room_size / 2;
	res.h = e->room_size / 2;
	res.x = tr->from->corr_x + (e->room_size / 4) + ((double)diff / (double)e->time_per_turn) * ((tr->to->corr_x + (e->room_size / 4) - (tr->from->corr_x + (e->room_size / 4))));
	res.y = tr->from->corr_y + (e->room_size / 4) + ((double)diff / (double)e->time_per_turn) * ((tr->to->corr_y + (e->room_size / 4) - (tr->from->corr_y + (e->room_size / 4))));
	return (res);
}

int	ft_get_angle(t_env *e, t_transition *tr)
{
	return (((atan2(tr->to->corr_y + e->room_size / 2 - (tr->from->corr_y + e->room_size / 2),
						tr->to->corr_x + e->room_size / 2 - (tr->from->corr_x + e->room_size / 2)) * 180 / M_PI) + 90));
}


void	ft_render_ants(t_env *e)
{
	t_list *ptr;
	t_transition *tr;
	SDL_Rect pos;
	SDL_Point center;
	int flip;
	ptr = e->anim.transitions;
	if ((SDL_GetTicks() - e->anim.start) % 200 < 100)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_NONE;
	while (ptr != NULL)
	{
		tr = (t_transition *)(ptr->content);
		tr->angle = ft_get_angle(e, tr);
		pos = ft_get_pos(e, tr);
		//SDL_RenderFillRect(e->sdl.renderer, &pos);
		center.x = pos.w / 2;
		center.y = pos.h / 2;
		//		if (rand() % 2 == 0)
		//	flip = SDL_FLIP_NONE;
		//		else
		SDL_RenderCopyEx(e->sdl.renderer, e->sdl.textures[ANT], NULL, &pos, tr->angle, &center, flip);
		ptr = ptr->next;
	}
}

void	ft_render_static_ants(t_env *e)
{
	t_list *ptr;
	t_room *room;
	SDL_Rect pos;
	SDL_Point center;

	ptr = e->anim.static_ants_rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		pos.x = room->corr_x + e->room_size / 4;
		pos.y = room->corr_y + e->room_size / 4;
		pos.w = e->room_size / 2;
		pos.h = e->room_size / 2;
		center.x = pos.w / 2;
		center.y = pos.h / 2;
		SDL_RenderCopyEx(e->sdl.renderer, e->sdl.textures[ANT], NULL, &pos, 0, &center, SDL_FLIP_NONE);
		ptr = ptr->next;
	}
}

void ft_render(t_env *e)
{
	SDL_SetRenderDrawColor( e->sdl.renderer, 100, 100, 100, 255);
	SDL_RenderClear(e->sdl.renderer);
	//	SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[BG], NULL, NULL);
	ft_render_links(e);
	ft_render_rooms(e);
	ft_render_ants(e);
	ft_render_static_ants(e);
	SDL_RenderPresent(e->sdl.renderer);
}

void ft_render_visu(t_env *e, char *str)
{
	int loop;
	SDL_Event event;
	ft_add_transitions(e, str);
	ft_add_static(e);
	e->anim.start = SDL_GetTicks();
	loop = 1;
	while (SDL_GetTicks() < e->anim.start + e->time_per_turn)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT ||
					(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				exit(0);
			else if (event.type == SDL_KEYDOWN)
				ft_key_down(e, event);
			else if (event.type == SDL_KEYUP)
				ft_key_up(e, event);
			else if(event.type == SDL_MOUSEBUTTONDOWN)
				ft_mouse_down(e, event);
			else if(event.type == SDL_MOUSEBUTTONUP)
				ft_mouse_up(e, event);
			else if(event.type == SDL_MOUSEMOTION)
				ft_mouse_motion(e, event);
		}
		ft_process(e);
		ft_render(e);
		SDL_Delay(16);
	}
}

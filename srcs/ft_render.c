/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 02:30:10 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/31 01:50:17 by ldedier          ###   ########.fr       */
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
			SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[START_SPRITE + (room == e->selected_room) * 3], NULL, &pos);
		else if (room == e->lem.map.end)
			SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[END_SPRITE + (room == e->selected_room) * 3], NULL, &pos);
		else
			SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[ROOM + (room == e->selected_room) * 3], NULL, &pos);
		ptr = ptr->next;
	}
}

/*
** return the position of moving ant at the very instant
*/
SDL_Rect	ft_get_pos(t_env *e, t_transition *tr)
{
	SDL_Rect res;

	res.w = e->room_size / 2;
	res.h = e->room_size / 2;
	res.x = tr->from->corr_x + ((double)e->room_size / 4) + (e->anim.progress) * ((tr->to->corr_x + (e->room_size / 4) - (tr->from->corr_x + (e->room_size / 4))));
	res.y = tr->from->corr_y + ((double)e->room_size / 4) + (e->anim.progress) * ((tr->to->corr_y + (e->room_size / 4) - (tr->from->corr_y + (e->room_size / 4))));
	return (res);
}

int	ft_get_angle(t_env *e, t_transition *tr)
{
	return (((atan2(tr->to->corr_y + e->room_size / 2 - (tr->from->corr_y + e->room_size / 2),
						tr->to->corr_x + e->room_size / 2 - (tr->from->corr_x + e->room_size / 2)) * 180 / M_PI) + 90));
}

/*
SDL_Texture *ft_get_ant_texture(t_env *e)
{
	SDL_Texture *texture;

	return texture;
}
*/
void	ft_render_ants(t_env *e)
{
	t_list *ptr;
	t_transition *tr;
	SDL_Rect pos;
	SDL_Point center;

	if (!e->anim.pause)
		e->anim.current_animation = ((SDL_GetTicks() - e->anim.start) % 400) / 100;
//	texture = e->sdl.ant_textures[3];
	//int flip;
	ptr = e->anim.transitions;
//	if ((SDL_GetTicks() - e->anim.start) % 200 < 100)
//		flip = SDL_FLIP_HORIZONTAL;
//	else
//		flip = SDL_FLIP_NONE;
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
		SDL_RenderCopyEx(e->sdl.renderer, e->sdl.ant_textures[e->anim.current_animation], NULL, &pos, tr->angle, &center, SDL_FLIP_NONE);
		ptr = ptr->next;
	}
}

void	ft_process_animation(t_env *e)
{
	int diff;

	e->anim.current = SDL_GetTicks();
	diff = e->anim.current - e->anim.previous;
	e->anim.progress = ft_fmin(1, e->anim.progress + (double)diff / e->time_per_turn);
	e->anim.previous = e->anim.current;
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

void	ft_render_selected_room(t_env *e)
{
	char		*str;
	SDL_Rect	pos;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface *textSurface;
	SDL_Texture *texture;
	str = ft_strjoin("room: ", e->selected_room->name);
	
	textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], str, color);
	texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	SDL_FreeSurface(textSurface);
	pos.x = 1280 - (ft_strlen(str) * 10);
	pos.y = 140;
	pos.w = ft_strlen(str) * 20;
	pos.h = 45;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	ft_strdel(&str);
}

void	ft_render_turn(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface *textSurface;
	SDL_Texture *texture;
	str2 = ft_itoa(e->lem.turn);
	str = ft_strjoin("turn #", str2);

	pos.x = 1280 - ft_strlen(str) * 15;
	pos.y = 65;
	pos.w = ft_strlen(str) * 30;
	pos.h = 70;

	textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], str, color);
	texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	ft_strdel(&str);
	ft_strdel(&str2);
}
void	ft_render_speed(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface *textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], "time per turn:", color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	SDL_FreeSurface(textSurface);

	pos.x = 2200;
	pos.y = 60;
	pos.w = 14 * 20;
	pos.h = 45;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	str2 = ft_itoa(e->time_per_turn);
	str = ft_strjoin(str2, " ms");
	textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], str, color);
	texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	SDL_FreeSurface(textSurface);
	pos.x = 2330 - (ft_strlen(str) * 10);
	pos.y = 110;
	pos.w = ft_strlen(str) * 20;
	pos.h = 45;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	ft_strdel(&str);
	ft_strdel(&str2);
}

void	ft_render_nb_ants_start(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface *textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], "beginning:", color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	SDL_FreeSurface(textSurface);

	pos.x = 20;
	pos.y = 20;
	pos.w = 10 * 20;
	pos.h = 45;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	str2 = ft_itoa(e->lem.map.start->ant_count);
	if (e->lem.map.start->ant_count == 1)
		str = ft_strjoin(str2, " ant");
	else
		str = ft_strjoin(str2, " ants");
	textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], str, color);
	texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	SDL_FreeSurface(textSurface);
	pos.x = 250;
	pos.w = ft_strlen(str) * 20;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	ft_strdel(&str);
	ft_strdel(&str2);
}

void	ft_render_nb_ants_end(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface *textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], "end:", color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	SDL_FreeSurface(textSurface);

	pos.x = 20;
	pos.y = 80;
	pos.w = 4 * 20;
	pos.h = 45;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	str2 = ft_itoa(e->lem.map.end->ant_count - e->lem.map.toward_end);


	if (e->lem.map.end->ant_count - e->lem.map.toward_end == 1)
		str = ft_strjoin(str2, " ant");
	else
		str = ft_strjoin(str2, " ants");
	textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], str, color);
	texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	SDL_FreeSurface(textSurface);
	pos.x = 250;
	pos.w = ft_strlen(str) * 20;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	ft_strdel(&str);
	ft_strdel(&str2);
}

void	ft_render_nb_ants_others(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface *textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], "others:", color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);

	pos.x = 20;
	pos.y = 140;
	pos.w = 7 * 20;
	pos.h = 45;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	str2 = ft_itoa(e->lem.map.total_ants - (e->lem.map.start->ant_count + (e->lem.map.end->ant_count - e->lem.map.toward_end)));
	if (e->lem.map.total_ants - (e->lem.map.start->ant_count + (e->lem.map.end->ant_count - e->lem.map.toward_end)) == 1)
		str = ft_strjoin(str2, " ant");
	else
		str = ft_strjoin(str2, " ants");
	textSurface = TTF_RenderText_Solid(e->sdl.fonts[0], str, color);
	texture = SDL_CreateTextureFromSurface(e->sdl.renderer, textSurface);
	pos.x = 250;
	pos.w = ft_strlen(str) * 20;
	SDL_RenderCopy(e->sdl.renderer, texture, NULL, &pos);
	SDL_DestroyTexture(texture);
	ft_strdel(&str);
	ft_strdel(&str2);
}
void	ft_render_nb_ants(t_env *e)
{
	ft_render_nb_ants_start(e);
	ft_render_nb_ants_end(e);
	ft_render_nb_ants_others(e);
	ft_render_speed(e);
	if (e->selected_room != NULL)
		ft_render_selected_room(e);
}

void	ft_render_dashboard(t_env *e)
{
	SDL_Rect rect;
	
	rect.x = 0;
	rect.y = 0;
	rect.w = e->dim.width;
	rect.h = GRASS_BORDER;
	SDL_SetRenderDrawColor( e->sdl.renderer, 50, 50, 50, 255);
	SDL_RenderFillRect(e->sdl.renderer, &rect);
	ft_render_nb_ants(e);
	ft_render_turn(e);
}

void ft_render(t_env *e)
{
	SDL_SetRenderDrawColor( e->sdl.renderer, 100, 100, 100, 255);
	SDL_RenderClear(e->sdl.renderer);
	//	SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[BG], NULL, NULL);
	ft_render_dashboard(e);
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
	e->lem.map.toward_end = 0;
	ft_add_transitions(e, str);
	ft_add_static(e);
	e->anim.start = SDL_GetTicks();
	e->anim.previous = e->anim.start;
	e->anim.progress = 0;
	loop = 1;
	while (e->anim.progress < 1)
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
		if (!e->anim.pause)
			ft_process_animation(e);
		ft_process(e);
		ft_render(e);
		SDL_Delay(20);
	}
}

void ft_render_visu_end(t_env *e)
{
	int loop;
	SDL_Event event;

	e->lem.map.toward_end = 0;
	loop = 1;
	while (loop)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT ||
					(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				loop = 0;
			else if (event.type == SDL_KEYUP)
				ft_key_up(e, event);
			else if(event.type == SDL_MOUSEBUTTONDOWN)
				ft_mouse_down(e, event);
			else if(event.type == SDL_MOUSEBUTTONUP)
				ft_mouse_up(e, event);
			else if(event.type == SDL_MOUSEMOTION)
				ft_mouse_motion(e, event);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
				ft_reset_pos(e);
		}
		ft_process_end(e);
		ft_render(e);
		SDL_Delay(20);
	}
}

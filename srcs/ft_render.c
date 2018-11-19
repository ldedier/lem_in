/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:51:01 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/18 19:42:05 by ldedier          ###   ########.fr       */
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
			SDL_RenderDrawLine(e->sdl.renderer, room->corr_x + e->room_size / 2,
				room->corr_y + e->room_size / 2,
				((t_room *)(neigh_ptr->content))->corr_x + e->room_size / 2,
				((t_room *)(neigh_ptr->content))->corr_y + e->room_size / 2);
			neigh_ptr = neigh_ptr->next;
		}
		ptr = ptr->next;
	}
}

void ft_render_room(t_env *e, t_room *room, SDL_Rect *pos)
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
	t_list *ptr;
	t_room *room;
	SDL_Rect pos;
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

/*
** return the position of moving ant at the very instant
*/
SDL_Rect	ft_get_pos(t_env *e, t_transition *tr)
{
	SDL_Rect res;

	res.w = e->room_size / 2;
	res.h = e->room_size / 2;
	res.x = tr->from->corr_x + ((double)e->room_size / 4) +
		(e->anim.progress) * ((tr->to->corr_x + (e->room_size / 4) -
					(tr->from->corr_x + (e->room_size / 4))));
	res.y = tr->from->corr_y + ((double)e->room_size / 4) +
		(e->anim.progress) * ((tr->to->corr_y + (e->room_size / 4) -
					(tr->from->corr_y + (e->room_size / 4))));
	return (res);
}

int	ft_get_angle(t_env *e, t_transition *tr)
{
	return (((atan2(tr->to->corr_y + e->room_size / 2 - 
				(tr->from->corr_y + e->room_size / 2),
				tr->to->corr_x + e->room_size / 2 -
					(tr->from->corr_x + e->room_size / 2)) * 180 / M_PI) + 90));
}

int		ft_dist_transition(t_transition *tr)
{
	return ft_dist(tr->from->corr_x, tr->from->corr_y,
					tr->to->corr_x, tr->to->corr_y);
}

void	ft_render_ants(t_env *e)
{
	t_list *ptr;
	t_transition *tr;
	SDL_Rect pos;
	SDL_Point center;
	int current_animation;

	ptr = e->anim.transitions;
	while (ptr != NULL)
	{
		tr = (t_transition *)(ptr->content);
		tr->angle = ft_get_angle(e, tr);
		pos = ft_get_pos(e, tr);
		center.x = pos.w / 2;
		center.y = pos.h / 2;
		current_animation = (((int)(e->anim.progress * 4 *
				(ft_dist_transition(tr) * 0.025))) % 4);
		SDL_RenderCopyEx(e->sdl.renderer,
				e->sdl.ant_textures[current_animation], NULL, &pos,
					tr->angle, &center, SDL_FLIP_NONE);
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

int		ft_use_texture_with_surface(t_env *e, char *str)
{
	if (!(e->sdl.surface = TTF_RenderText_Solid(e->sdl.font, str, e->sdl.color)))
		return (1);
	if (!(e->sdl.texture = SDL_CreateTextureFromSurface(e->sdl.renderer, e->sdl.surface)))
	{
		SDL_FreeSurface(e->sdl.surface);
		return (1);
	}
	SDL_FreeSurface(e->sdl.surface);
	return (0);
}

void	ft_fill_rect_x_y(SDL_Rect *rect, int x, int y)
{
	rect->x = x;
	rect->y = y;
}

void	ft_fill_rect_w_h(SDL_Rect *rect, int w, int h)
{
	rect->w = w;
	rect->h = h;
}

int		ft_free_turn(char *str, int ret)
{
	free(str);
	return (ret);
}

int		ft_render_selected_room(t_env *e)
{
	char		*str;
	SDL_Rect	pos;
	double		scale;

	scale = 10.0 * e->react.w_scale;
	if (!(str = ft_strjoin("room: ", e->selected_room->name)))
		return (1);
	if (ft_use_texture_with_surface(e, str))
		return (1);
	ft_fill_rect_x_y(&pos, (e->dim.width / 2) - (ft_strlen(str) * scale),
		e->react.h_scale * 140);
	ft_fill_rect_w_h(&pos, ft_strlen(str) * 2 * scale, 45 * e->react.h_scale);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &pos);
	SDL_DestroyTexture(e->sdl.texture);
	ft_strdel(&str);
	return (0);
}

int		ft_render_turn(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	int			scale;

	scale = 15.0 * e->react.w_scale;
	if (!(str2 = ft_itoa(e->lem.turn)))
		return (1);
	if (!(str = ft_strjoin("turn #", str2)))
		return (ft_free_turn(str2, 1));
	ft_strdel(&str2);
	ft_fill_rect_x_y(&pos,  (e->dim.width / 2) - ft_strlen(str) * scale,
		65 * e->react.h_scale);
	ft_fill_rect_w_h(&pos, ft_strlen(str) * 2 * scale, 70 * e->react.h_scale);
	if (ft_use_texture_with_surface(e, str))
		return (ft_free_turn(str, 1));
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &pos);
	SDL_DestroyTexture(e->sdl.texture);
	ft_strdel(&str);
	return (0);
}

int ft_render_speed_value(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	int			scale;

	scale = 10.0 * e->react.w_scale;
	if (!(str2 = ft_itoa(e->time_per_turn)))
		return (1);
	if (!(str = ft_strjoin(str2, " ms")))
		return (ft_free_turn(str2, 1));
	ft_strdel(&str2);
	if (ft_use_texture_with_surface(e, str))
		return (ft_free_turn(str, 1));
	ft_fill_rect_x_y(&pos, e->dim.width - ((230.0 / 2560) * e->dim.width) -
		(ft_strlen(str) * scale), 110 * e->react.h_scale);
	ft_fill_rect_w_h(&pos, ft_strlen(str) * 2 * scale, 45 * e->react.h_scale);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &pos);
	SDL_DestroyTexture(e->sdl.texture);
	ft_strdel(&str);
	return (0);
}
int		ft_render_speed(t_env *e)
{
	SDL_Rect	pos;
	int scale;

	scale = 10.0 * e->react.w_scale;

	if (ft_use_texture_with_surface(e, "time per turn"))
		return (1);

	ft_fill_rect_x_y(&pos, e->dim.width - ((230.0 / 2560) * e->dim.width) -
		(14 * scale), 60 * e->react.h_scale);
	ft_fill_rect_w_h(&pos, 14 * 2 * scale, 45 * e->react.h_scale);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &pos);
	SDL_DestroyTexture(e->sdl.texture);
	return (ft_render_speed_value(e));
}

int		ft_render_nb_ants_rect(SDL_Rect *pos, char *title,
			int value, t_env *e)
{
	char		*str;
	char		*str2;

	if (ft_use_texture_with_surface(e, title))
		return (1);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, pos);
	SDL_DestroyTexture(e->sdl.texture);
	if (!(str2 = ft_itoa(value)))
		return (1);
	if (!(str = ft_strjoin(str2, value == 1 ? " ant" : " ants")))
		return (ft_free_turn(str2, 1));
	ft_strdel(&str2);
	if (ft_use_texture_with_surface(e, str))
		return (ft_free_turn(str, 1));
	pos->x = 250 * e->react.w_scale;
	pos->w = ft_strlen(str) * 20 * e->react.w_scale;
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, pos);
	SDL_DestroyTexture(e->sdl.texture);
	ft_strdel(&str);
	return (0);
}

int		ft_render_nb_ants_start(t_env *e)
{
	SDL_Rect	pos;

	pos.x = 20 * e->react.w_scale;
	pos.y = 20 * e->react.h_scale;
	pos.w = 200 * e->react.w_scale;
	pos.h = 45 * e->react.h_scale;

	return (ft_render_nb_ants_rect(&pos, "beginning:",
		e->lem.map.start->ant_count, e));
}

int		ft_render_nb_ants_end(t_env *e)
{
	SDL_Rect	pos;

	pos.x = 20 * e->react.w_scale;
	pos.y = 80 * e->react.h_scale;
	pos.w = 80 * e->react.w_scale;
	pos.h = 45 * e->react.h_scale;

	return (ft_render_nb_ants_rect(&pos, "end:",
		e->lem.map.end->ant_count - e->toward_end, e));
}

int		ft_render_nb_ants_others(t_env *e)
{

	SDL_Rect	pos;

	pos.x = 20 * e->react.w_scale;
	pos.y = 140 * e->react.h_scale;
	pos.w = 140 * e->react.w_scale;
	pos.h = 45 * e->react.h_scale;

	return (ft_render_nb_ants_rect(&pos, "others:",
		e->lem.map.total_ants - (e->lem.map.start->ant_count +
			(e->lem.map.end->ant_count - e->toward_end)), e));
}

int		ft_render_nb_ants(t_env *e)
{
	if (ft_render_nb_ants_start(e))
		return (1);
	if (ft_render_nb_ants_end(e))
		return (1);	
	if (ft_render_nb_ants_others(e))
		return (1);
	return (0);
}

int		ft_render_dashboard(t_env *e)
{
	SDL_Rect rect;
	
	rect.x = 0;
	rect.y = 0;
	rect.w = e->dim.width;
	rect.h = e->react.grass_border;
	SDL_SetRenderDrawColor( e->sdl.renderer, 50, 50, 50, 255);
	SDL_RenderFillRect(e->sdl.renderer, &rect);
	if (ft_render_nb_ants(e))
		return (1);
	if (ft_render_turn(e))
		return (1);
	if (ft_render_speed(e))
		return (1);
	if (e->selected_room != NULL)
	{
		if (ft_render_selected_room(e))
			return (1);
	}
	return (0);
}

int		ft_render(t_env *e)
{
	SDL_SetRenderDrawColor( e->sdl.renderer, 100, 100, 100, 255);
	SDL_RenderClear(e->sdl.renderer);
	if (ft_render_dashboard(e))
		return (1);
	ft_render_links(e);
	ft_render_rooms(e);
	ft_render_ants(e);
	ft_render_static_ants(e);
	SDL_RenderPresent(e->sdl.renderer);
	return (0);
}

int		ft_add_current_ants(t_env *e, char *str)
{
	if (ft_add_transitions(e, str))
	{
		ft_lstdel_value(&(e->anim.transitions));
		ft_lstdel_ptr(&(e->anim.static_ants_rooms));
		return (1);
	}
	if (ft_add_static(e))
	{
		ft_lstdel_value(&(e->anim.transitions));
		ft_lstdel_ptr(&(e->anim.static_ants_rooms));
		return (1);
	}
	return (0);
}

void		ft_process_current_turn(t_env *e, int *loop)
{
	SDL_Event	event;
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN &&
				 event.key.keysym.sym == SDLK_ESCAPE))
			*loop = 0;
		else if (event.type == SDL_KEYDOWN && !event.key.repeat)
			ft_key_down(e, event.key.keysym.sym);
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			ft_mouse_down(e, event);
		else if (event.type == SDL_MOUSEBUTTONUP)
			ft_mouse_up(e, event);
		else if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(e, event);
	}
	if (!e->anim.pause)
		ft_process_animation(e);
	ft_process(e, SDL_GetKeyboardState(NULL));
	ft_render(e);
	SDL_Delay(20);
}

int		ft_render_visu(t_env *e, char *str)
{
	int			loop;

	e->toward_end = 0;
	if (ft_add_current_ants(e, str))
		return (-1);
	e->anim.start = SDL_GetTicks();
	e->anim.previous = e->anim.start;
	e->anim.progress = 0;
	loop = 1;
	while (loop == 1 && e->anim.progress < 1)
		ft_process_current_turn(e, &loop);
	ft_lstdel_value(&(e->anim.transitions));
	ft_lstdel_ptr(&(e->anim.static_ants_rooms));
	return (loop);
}

void	ft_process_end_events(t_env *e, int *loop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN &&
				 event.key.keysym.sym == SDLK_ESCAPE))
			*loop = 0;
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			ft_mouse_down(e, event);
		else if (event.type == SDL_MOUSEBUTTONUP)
			ft_mouse_up(e, event);
		else if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(e, event);
		else if (event.type == SDL_KEYDOWN &&
				event.key.keysym.sym == SDLK_r)
			ft_reset_pos(e);
	}
}

void	ft_render_visu_end(t_env *e)
{
	int loop;

	e->toward_end = 0;
	loop = 1;
	while (loop)
	{
		ft_process_end_events(e, &loop);
		ft_process_end(e);
		ft_render(e);
		SDL_Delay(20);
	}
}

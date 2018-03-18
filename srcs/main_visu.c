/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/18 19:21:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int		ft_iz_okay(t_env *e)
{
	double w_alpha;
	double h_alpha;
	t_list *ptr;
	t_list *ptr2;
	t_room *room;
	t_room *room2;

	ptr = e->lem.map.rooms;
	w_alpha = (double)((double)(9.0 * WIN_WIDTH) / ((double)(10.0 * ((double)e->stats.right - e->stats.left)))) - (double)e->room_size / (double)(e->stats.right - e->stats.left);
	h_alpha = (double)((9.0 * (WIN_HEIGHT - GRASS_BORDER)) / ((double)(10.0 * ((double)e->stats.bottom - e->stats.top)))) - (double)e->room_size / (double)(e->stats.bottom - e->stats.top);

	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		ptr2 = e->lem.map.rooms;
		while (ptr2 != NULL)
		{
			room2 = (t_room *)(ptr2->content);
			if (room != room2 && sqrt(pow(room->x * w_alpha - room2->x * w_alpha, 2) + pow(room->y * h_alpha - room2->y * h_alpha, 2)) <= e->room_size)
			{
				ft_printf("room1:%s\nroom2:%s\n", room->name, room2->name);
				return (0);
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return (1);
}

void	ft_update_room_size(t_env *e)
{
	e->room_size = ROOM_SIZE;
	while (!ft_iz_okay(e))
	{
		e->room_size -= 10;
		ft_printf("%d\n", e->room_size);
	}
}

void	ft_update_corr_pos(t_env *e)
{
	double w_alpha;
	double h_alpha;
	t_list *ptr;
	t_room *room;
	int x_margin;
	int y_margin;

	ptr = e->lem.map.rooms;
	ft_update_room_size(e);
	w_alpha = (double)((double)(9.0 * WIN_WIDTH) / ((double)(10.0 * ((double)e->stats.right - e->stats.left)))) - (double)e->room_size / (double)(e->stats.right - e->stats.left);
	h_alpha = (double)((9.0 * (WIN_HEIGHT - GRASS_BORDER)) / ((double)(10.0 * ((double)e->stats.bottom - e->stats.top)))) - (double)e->room_size / (double)(e->stats.bottom - e->stats.top);

	//	if (w_alpha > h_alpha)
//	{
//		x_margin = (WIN_WIDTH / 20) - (e->stats.left * w_alpha) - e->room_size / 2;
//		y_margin = ((WIN_HEIGHT - GRASS_BORDER) / 20) - (e->stats.top * h_alpha) + GRASS_BORDER - e->room_size / 2;
//	}
//	else
//	{
		x_margin = (WIN_WIDTH / 20) - (e->stats.left * w_alpha);
		y_margin = ((WIN_HEIGHT - GRASS_BORDER) / 20) - (e->stats.top * h_alpha) + GRASS_BORDER;
//	}
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		room->corr_x_init = x_margin + room->x * w_alpha;
		room->corr_y_init = y_margin + room->y * h_alpha;
		room->corr_x = room->corr_x_init;
		room->corr_y = room->corr_y_init;
		ptr = ptr->next;
	}
}

int	ft_dist(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void	ft_draw_circle(SDL_Renderer *renderer, int x, int y, int radius)
{
	int i;
	int j;
	int center_x;
	int center_y;

	center_x = x + radius / 2;
	center_y = y + radius / 2;
	i = y;
	while (i < y + radius * 2)
	{
		j = x;
		while (j < x + radius * 2)
		{
			if (ft_dist(j, i, center_x, center_y) <= radius/2)
				SDL_RenderDrawPoint(renderer, j, i);
			j++;
		}
		i++;
	}
}

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
		if (room == e->lem.map.start)
			SDL_SetRenderDrawColor( e->sdl.renderer, 0, 0, 255, 255);
		else if (room == e->lem.map.end)
			SDL_SetRenderDrawColor( e->sdl.renderer, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor( e->sdl.renderer, 255, 255, 255, 255);
		pos.x = room->corr_x;
		pos.y = room->corr_y;
	//	ft_draw_circle(e->sdl.renderer, pos.x, pos.y, pos.w);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[ROOM], NULL, &pos);
	//	SDL_RenderFillRect(e->sdl.renderer, &pos);
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
void ft_render(t_env *e)
{
	SDL_SetRenderDrawColor( e->sdl.renderer, 100, 100, 100, 255);
	SDL_RenderClear(e->sdl.renderer);
//	SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[BG], NULL, NULL);
	ft_render_links(e);
	ft_render_rooms(e);
	ft_render_ants(e);
	SDL_RenderPresent(e->sdl.renderer);
}

t_transition *ft_new_transition(t_env *e, t_room *from, t_room *to, int ant_num)
{
	t_transition *res;

	if (!from || !to)
	{
		ft_printf("ERROR NEW TRANSITION");
		exit(1);
	}
	res = (t_transition *)(malloc(sizeof(t_transition)));
	from->ant_count--;
	if (from == e->lem.map.start)
	{
		if (from->ant_count == 0)
			from->ant_number = 0;
		else
			from->ant_number++;
	}
	else
		from->ant_number = 0;
	to->ant_count++;
	to->ant_number = ant_num;
	res->from = from;
	res->to = to;
	res->ant_num = ant_num;
	res->angle = ft_get_angle(e, res);
	return (res);
}

void	ft_affich_transitions(t_env *e)
{
	t_list *ptr;
	t_transition *tr;

	ptr = e->anim.transitions;
	while (ptr != NULL)
	{
		tr = (t_transition *)(ptr->content);
		ft_printf("from: %s\n", tr->from->name);
		ft_printf("to: %s\n", tr->to->name);
		ft_printf("by ant #%d\n\n", tr->ant_num);
		ptr = ptr->next;
	}
}

void	ft_add_transition(t_env *e, int ant_numero, char *room_name)
{
	t_room *from;
	t_room *to;
	t_list *ptr;
	t_room *room;
	t_transition *transition;

	ptr = e->lem.map.rooms;
	from = NULL;
	to = NULL;
	while (ptr != NULL && (from == NULL || to == NULL))
	{
		room = (t_room *)(ptr->content);
		if (room->ant_number == ant_numero)
			from = room;
		else if (!ft_strcmp(room->name, room_name))
			to = room;
		ptr = ptr->next;
	}
	transition = ft_new_transition(e, from, to, ant_numero);
	ft_lstpushback(&(e->anim.transitions), ft_lstnew_ptr(transition, sizeof(t_transition)));
}

void	ft_add_transitions(t_env *e, char *str)
{
	char **split;
	int i;
	char **ant_split;

	i = 0;
	split = ft_strsplit(str,' ');
	while (split[i])
	{
		ant_split = ft_strsplit(split[i], '-');
	//	ft_printf("num ant: %d\n", ft_atoi(&(ant_split[0][1])));
	//	ft_printf("name room: %s\n\n", ant_split[1]);
		ft_add_transition(e, ft_atoi(&(ant_split[0][1])), ant_split[1]);
		i++;
	}
}

void	ft_reset_pos(t_env *e)
{
	t_list *ptr;
	t_room *room;

	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		room->corr_x = room->corr_x_init;
		room->corr_y = room->corr_y_init;
		ptr = ptr->next;
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
}

void	ft_process(t_env *e)
{
	if (e->keys.up && e->time_per_turn > 100)
	{
		e->time_per_turn -= 100;
	}
	if (e->keys.down)
	{
		e->time_per_turn += 100;
	}
}

void	ft_grab_room(t_env *e, int x, int y)
{

	ft_printf("x:%d\ny:%d\n",x, y);
	t_list *ptr;
	t_room *room;
	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (x >= room->corr_x && x <= room->corr_x + e->room_size &&
				y >= room->corr_y && y <= room->corr_y + e->room_size)
		{
			e->grab.grabbed_room = room;
			e->grab.x_diff = room->corr_x - x;
			e->grab.y_diff = room->corr_y - y;
			ft_printf("LE NOM: %s\n", room->name);
			return;
		}
		ptr = ptr->next;
	}
}	

void	ft_mouse_down(t_env *e, SDL_Event event)
{
	ft_printf("LOOOOOOOOL");
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
		e->grab.grabbed_room->corr_x = event.motion.x + e->grab.x_diff;
		e->grab.grabbed_room->corr_y = event.motion.y + e->grab.y_diff;
	}
}

void render_visu(t_env *e, char *str)
{
	int loop;
	SDL_Event event;
	ft_add_transitions(e, str);
//	ft_affich_transitions(e);
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

int		ft_parse_visu(t_lem *lem)
{
	char	*str;
	int		ret;

	t_parse_func parse_arr[5];
	ft_init_parser(&(lem->parser));
	ft_init_parse_arr(parse_arr);
	while ((ret = get_next_line(0, &str)) > 0 && ft_strcmp(str, ""))
	{
		if (parse_arr[lem->parser.phase](str, lem) == -1)
			return (-1);
	}
	return (0);
}

void	ft_update_stats(t_room *room, t_env *e)
{
	if (room->x < e->stats.left || !e->stats.left_fix)
	{
		e->stats.left = room->x;
		e->stats.left_fix = 1;
	}
	if (room->x > e->stats.right || !e->stats.right_fix)
	{
		e->stats.right = room->x;
		e->stats.right_fix = 1;
	}
	if (room->y > e->stats.bottom || !e->stats.bottom_fix)
	{
		e->stats.bottom = room->y;
		e->stats.bottom_fix = 1;
	}
	if (room->y < e->stats.top || !e->stats.top_fix)
	{
		e->stats.top = room->y;
		e->stats.top_fix = 1;
	}
}

void	ft_gather_stats(t_env *e)
{
	t_list *ptr;
	t_room *room;

	ptr = e->lem.map.rooms;
	e->stats.top_fix = 0;
	e->stats.bottom_fix = 0;
	e->stats.right_fix = 0;
	e->stats.left_fix = 0;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		ft_update_stats(room, e);
		ptr = ptr->next;
	}
}

void	ft_debug_stats(t_stats* stats)
{
	ft_printf("top:%d\n", stats->top);
	ft_printf("bottom:%d\n", stats->bottom);
	ft_printf("left:%d\n", stats->left);
	ft_printf("right:%d\n", stats->right);
}

void	ft_update_room(t_map *map, int ant_num, char *room_name)
{
	t_list *ptr;
	t_room *room;

	ptr = map->rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (room->ant_number == ant_num)
		{
			room->ant_count--;
			if (room == map->start)
			{
				if (room->ant_count == 0)
					room->ant_number = 0;
				else
					room->ant_number++;
			}
			else
				room->ant_number = 0;
		}
		if (!ft_strcmp(room_name, room->name))
		{
			room->ant_count++;
			room->ant_number = ant_num;
		}
		ptr = ptr->next;
	}
}

void	ft_update_map(t_map *map, char *str)
{
	char **split;
	char **ant_split;
	int i;

	(void)map;
	i = 0;
	split = ft_strsplit(str, ' ');
	while (split[i])
	{
		ant_split = ft_strsplit(split[i], '-');
//		ft_printf("num ant: %d\n", ft_atoi(&(ant_split[0][1])));
//		ft_printf("name room: %s\n\n", ant_split[1]);
		ft_update_room(map, ft_atoi(&(ant_split[0][1])), ant_split[1]);
		i++;

	}
	ft_printf("%s\n", str);
}

int main(int argc, char **argv)
{
	t_env e;
	char *str;

	(void)argc;
	(void)argv;
	e.lem.map.rooms = NULL;
	e.anim.transitions = NULL;
	e.time_per_turn = TIME_PER_TURN;
	if (!ft_init_all(&e))
		ft_error("Initialisation error\n");
	if (ft_parse_visu(&(e.lem)) == -1)
		ft_error("Parsing error\n");
	//	ft_affich_map(&(e.lem.map));
	ft_gather_stats(&e);
	ft_update_corr_pos(&e);
//	ft_debug_stats(&(e.stats));
	while (get_next_line(0, &str) > 0)
	{
		render_visu(&e, str);
//		ft_update_map(&(e.lem.map), str);
//		ft_affich_map(&(e.lem.map));
		e.anim.transitions = NULL;
	}
	return (0);
}

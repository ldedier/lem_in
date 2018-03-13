/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/13 01:04:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_render_rooms(t_env *e)
{
	double alpha;
	t_list *ptr;
	t_room *room;
	SDL_Rect pos;
	SDL_Rect ant_pos;
	int	x_margin;
	int	y_margin;
	SDL_Point center;

	ptr = e->lem.map.rooms;
	alpha = ft_min((2.0 * WIN_WIDTH) / ((double)(3.0 * ((double)e->stats.right - e->stats.left))),
			(2.0 * WIN_HEIGHT) / ((double)(3.0 * ((double)e->stats.bottom - e->stats.top))));
	x_margin =  (WIN_WIDTH / 8) - e->stats.left * alpha;
	y_margin = (WIN_HEIGHT / 4) - e->stats.top * alpha;
	pos.w = ft_max(alpha / 1.5, ft_min(WIN_WIDTH / 50, WIN_HEIGHT / 40));
	pos.h = ft_max(alpha / 1.5, ft_min(WIN_WIDTH / 50, WIN_HEIGHT / 40));
	ant_pos.w = pos.w / 2;
	ant_pos.h = pos.h / 2;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (room == e->lem.map.start)
			SDL_SetRenderDrawColor( e->sdl.renderer, 0, 0, 255, 255);
		else if (room == e->lem.map.end)
			SDL_SetRenderDrawColor( e->sdl.renderer, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor( e->sdl.renderer, 255, 255, 255, 255);
		pos.x = x_margin + room->x * alpha;
		pos.y = y_margin + room->y * alpha;
		ant_pos.x = pos.x + pos.w / 4;
		ant_pos.y = pos.y + pos.h / 4;
		SDL_RenderFillRect(e->sdl.renderer, &pos);
		SDL_RenderCopyEx(e->sdl.renderer, e->sdl.textures[ANT], NULL, &ant_pos, 0, &center, SDL_FLIP_NONE);
		ptr = ptr->next;
	}
	//ft_printf("%f", alpha);
}

void ft_render(t_env *e)
{
	SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[BG], NULL, NULL);
	ft_render_rooms(e);
	SDL_RenderPresent(e->sdl.renderer);
}

void render_visu(t_env *e)
{
	int loop;
	SDL_Event event;

	loop = 1;
	while (loop)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || 
					(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				loop = 0;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_RIGHT:
						break;
					case SDLK_LEFT:
						break;
					case SDLK_DOWN:
						break;
					case SDLK_UP:
						break;
					default :
						break;
				}
			}
		}
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

int main(int argc, char **argv)
{
	t_env e;
	char *str;

	(void)argc;
	(void)argv;
	e.lem.map.rooms = NULL;
	if (!ft_init_all(&e))
		ft_error("Initialisation error\n");
	if (ft_parse_visu(&(e.lem)) == -1)
		ft_error("Parsing error\n");
	//	ft_affich_map(&(e.lem.map));
	ft_gather_stats(&e);
	ft_debug_stats(&(e.stats));
	while (get_next_line(0, &str) > 0)
	{
		render_visu(&e);
		ft_printf("%s\n", str);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:05:05 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 14:59:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_process_animation(t_env *e)
{
	int diff;

	e->anim.current = SDL_GetTicks();
	diff = e->anim.current - e->anim.previous;
	e->anim.progress = ft_fmin(1, e->anim.progress +
		(double)diff / e->time_per_turn);
	e->anim.previous = e->anim.current;
}

int		ft_use_texture_with_surface(t_env *e, char *str)
{
	if (!(e->sdl.surface = TTF_RenderText_Solid(e->sdl.font,
			str, e->sdl.color)))
		return (1);
	if (!(e->sdl.texture = SDL_CreateTextureFromSurface(e->sdl.renderer,
			e->sdl.surface)))
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

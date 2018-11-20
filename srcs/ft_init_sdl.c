/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sdl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:35:31 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 15:39:20 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_get_dimensions(t_env *e)
{
	SDL_DisplayMode dm;

	SDL_GetCurrentDisplayMode(0, &dm);
	e->dim.width = dm.w;
	e->dim.height = dm.h;
}

void	ft_init_sdl_to_null(t_env *e)
{
	e->sdl.window = NULL;
	e->sdl.renderer = NULL;
	e->sdl.w_surface = NULL;
}

int		ft_init_sdl_2(t_env *e)
{
	if (!(e->sdl.renderer = SDL_CreateRenderer(e->sdl.window, -1, 0)))
		return (1);
	if (SDL_RenderSetLogicalSize(e->sdl.renderer,
			e->sdl.screen.w, e->sdl.screen.h) < 0)
		return (1);
	if (SDL_SetRenderDrawColor(e->sdl.renderer, 0, 0, 0, 255) < 0)
		return (1);
	if (!(e->sdl.w_surface = SDL_CreateRGBSurface(0,
			e->dim.width, e->dim.height, 32, 0, 0, 0, 0)))
		return (1);
	return (0);
}

int		ft_init_sdl(t_env *e)
{
	e->sdl.screen.x = 300;
	e->sdl.screen.y = 200;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (1);
	if (TTF_Init() < 0)
		return (1);
	ft_get_dimensions(e);
	e->sdl.screen.w = e->dim.width;
	e->sdl.screen.h = e->dim.height;
	if (!(e->sdl.window = SDL_CreateWindow("lem-in visu",
		e->sdl.screen.x, e->sdl.screen.y, e->sdl.screen.w, e->sdl.screen.h,
			SDL_WINDOW_FULLSCREEN_DESKTOP)))
		return (1);
	if (ft_init_sdl_2(e))
		return (1);
	return (0);
}

int		ft_init_all_sdl(t_env *e)
{
	if (ft_init_sdl(e))
		return (1);
	if (ft_init_textures(e))
		return (1);
	e->sdl.color.r = 255;
	e->sdl.color.g = 255;
	e->sdl.color.b = 255;
	e->sdl.color.a = 255;
	e->react.w_scale = (double)e->dim.width / 2560.0;
	e->react.h_scale = (double)e->dim.height / 1440.0;
	e->react.grass_border = e->react.h_scale * GRASS_BORDER;
	return (0);
}

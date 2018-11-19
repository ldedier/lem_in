/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:17:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/19 19:26:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

SDL_Texture	*ft_load_texture(t_env *e, char *str)
{
	SDL_Texture *texture;

	texture = IMG_LoadTexture(e->sdl.renderer, str);
	if (texture == NULL)
		ft_file_error(str);
	return (texture);
}

TTF_Font	*ft_load_font(char *str, int quality)
{
	TTF_Font *font;

	font = TTF_OpenFont(str, quality);
	if (font == NULL)
		ft_file_error(str);
	return (font);
}

void		ft_init_textures_to_null(t_env *e)
{
	int i;

	i = 0;
	while (i < 8)
	{
		e->sdl.textures[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		e->sdl.ant_textures[i] = NULL;
		i++;
	}
}

int			ft_init_textures_2(t_env *e)
{
	if (!(e->sdl.textures[START_SEL] =
		ft_load_texture(e, PATH"/resources/octagon_red_selected.png")))
		return (1);
	if (!(e->sdl.textures[END_SEL] =
		ft_load_texture(e, PATH"/resources/octagon_blue_selected.png")))
		return (1);
	if (!(e->sdl.ant_textures[0] =
		ft_load_texture(e, PATH"/resources/ant_0_ref.png")))
		return (1);
	if (!(e->sdl.ant_textures[1] =
		ft_load_texture(e, PATH"/resources/ant_1_ref.png")))
		return (1);
	if (!(e->sdl.ant_textures[2] =
		ft_load_texture(e, PATH"/resources/ant_2_ref.png")))
		return (1);
	if (!(e->sdl.ant_textures[3] =
		ft_load_texture(e, PATH"/resources/ant_3_ref.png")))
		return (1);
	if (!(e->sdl.font = ft_load_font(PATH"/resources/workaholic.ttf", 80)))
		return (1);
	return (0);
}

int			ft_init_textures(t_env *e)
{
	if (!(e->sdl.textures[ANT] =
		ft_load_texture(e, PATH"/resources/ant_0.png")))
		return (1);
	if (!(e->sdl.textures[ROOM] =
		ft_load_texture(e, PATH"/resources/octagon.png")))
		return (1);
	if (!(e->sdl.textures[START_SPRITE] =
		ft_load_texture(e, PATH"/resources/octagon_red.png")))
		return (1);
	if (!(e->sdl.textures[END_SPRITE] =
		ft_load_texture(e, PATH"/resources/octagon_blue.png")))
		return (1);
	if (!(e->sdl.textures[ROOM_SEL] =
		ft_load_texture(e, PATH"/resources/octagon_selected.png")))
		return (1);
	if (ft_init_textures_2(e))
		return (1);
	return (0);
}

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

int			ft_init_sdl_2(t_env *e)
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

int			ft_init_sdl(t_env *e)
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

int			ft_init_all(t_env *e)
{
	ft_init_sdl_to_null(e);
	ft_init_textures_to_null(e);
	e->sdl.font = NULL;
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

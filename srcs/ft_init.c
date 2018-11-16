/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:17:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/16 16:43:08 by ldedier          ###   ########.fr       */
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

int			ft_init_textures(t_env *e)
{
	e->sdl.textures[ANT] = ft_load_texture(e, PATH"/resources/ant_0.png");
	e->sdl.textures[ROOM] = ft_load_texture(e, PATH"/resources/octagon.png");
	e->sdl.textures[START_SPRITE] = ft_load_texture(e, PATH"/resources/octagon_red.png");
	e->sdl.textures[END_SPRITE] = ft_load_texture(e, PATH"/resources/octagon_blue.png");
	e->sdl.textures[ROOM_SEL] = ft_load_texture(e, PATH"/resources/octagon_selected.png");
	e->sdl.textures[START_SEL] = ft_load_texture(e, PATH"/resources/octagon_red_selected.png");
	e->sdl.textures[END_SEL] = ft_load_texture(e, PATH"/resources/octagon_blue_selected.png");
	e->sdl.ant_textures[0] = ft_load_texture(e, PATH"/resources/ant_0_ref.png");
	e->sdl.ant_textures[1] = ft_load_texture(e, PATH"/resources/ant_1_ref.png");
	e->sdl.ant_textures[2] = ft_load_texture(e, PATH"/resources/ant_2_ref.png");
	e->sdl.ant_textures[3] = ft_load_texture(e, PATH"/resources/ant_3_ref.png");
	e->sdl.font = ft_load_font(PATH"/resources/workaholic.ttf", 80);
	return (1);
}

void	ft_get_dimensions(t_env *e)
{
	SDL_DisplayMode dm;

	SDL_GetCurrentDisplayMode(0, &dm);
	e->dim.width = dm.w;
	e->dim.height = dm.h;
}

int			ft_init_sdl(t_env *e)
{
	e->sdl.screen.x = 300;
	e->sdl.screen.y = 200;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (0);
	if (TTF_Init() < 0)
		return(0);
	ft_get_dimensions(e);
	e->sdl.screen.w = e->dim.width;
	e->sdl.screen.h = e->dim.height;
	if (!(e->sdl.window = SDL_CreateWindow("lem-in visu",
		e->sdl.screen.x, e->sdl.screen.y, e->sdl.screen.w, e->sdl.screen.h, SDL_WINDOW_FULLSCREEN_DESKTOP)))
//		e->sdl.screen.x, e->sdl.screen.y, e->sdl.screen.w, e->sdl.screen.h, SDL_WINDOW_HIDDEN)))
		return (0);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (0);
	Mix_VolumeMusic(32);
	e->sdl.renderer = SDL_CreateRenderer(e->sdl.window, -1, 0);
	if (e->sdl.renderer == NULL)
		return (0);
	if (SDL_RenderSetLogicalSize(e->sdl.renderer,
				e->sdl.screen.w, e->sdl.screen.h) < 0)
		return (0);
	if (SDL_SetRenderDrawColor(e->sdl.renderer, 0, 0, 0, 255) < 0)
		return (0);
	e->sdl.surface = SDL_CreateRGBSurface(0,
			e->dim.width, e->dim.height, 32, 0, 0, 0, 0);
	if (e->sdl.surface == NULL)
		return (0);
	return (1);
}

int			ft_init_all(t_env *e)
{
	if (!ft_init_sdl(e))
		return (0);
	if (!ft_init_textures(e))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:17:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/13 00:36:32 by ldedier          ###   ########.fr       */
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

int			ft_init_textures(t_env *e)
{
	e->sdl.textures[ANT] = ft_load_texture(e, PATH"/resources/ant.png");
	e->sdl.textures[BG] = ft_load_texture(e, PATH"/resources/swag.png");
	return (1);
}

int			ft_init_sdl(t_env *e)
{
	e->sdl.screen.x = 300;
	e->sdl.screen.y = 200;
	e->sdl.screen.w = WIN_WIDTH;
	e->sdl.screen.h = WIN_HEIGHT;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (0);
	if (!(e->sdl.window = SDL_CreateWindow("lem-in visu",
		e->sdl.screen.x, e->sdl.screen.y, e->sdl.screen.w, e->sdl.screen.h, 0)))
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
			WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0);
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

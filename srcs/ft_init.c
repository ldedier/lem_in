/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:17:44 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 17:30:28 by ldedier          ###   ########.fr       */
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

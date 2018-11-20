/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:57:36 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 15:59:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_free_texture(SDL_Texture *texture)
{
	if (texture != NULL)
		SDL_DestroyTexture(texture);
}

void	ft_free_font(TTF_Font *font)
{
	if (font != NULL)
		TTF_CloseFont(font);
}

void	ft_free_textures(t_env *e)
{
	int i;

	i = 0;
	while (i < 8)
	{
		ft_free_texture(e->sdl.textures[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		ft_free_texture(e->sdl.ant_textures[i]);
		i++;
	}
}

void	ft_free_all(t_env *e)
{
	ft_lstdel_value(&(e->vants));
	ft_delete_rooms(&(e->lem.map.rooms));
	ft_free_textures(e);
	ft_free_font(e->sdl.font);
	if (e->sdl.w_surface)
		SDL_FreeSurface(e->sdl.w_surface);
	if (e->sdl.renderer)
		SDL_DestroyRenderer(e->sdl.renderer);
	if (e->sdl.window)
		SDL_DestroyWindow(e->sdl.window);
	if (TTF_WasInit())
		TTF_Quit();
	if (SDL_WasInit(SDL_INIT_EVERYTHING))
		SDL_Quit();
}

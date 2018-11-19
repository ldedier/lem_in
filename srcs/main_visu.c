/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/19 19:17:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_init_env(t_env *e)
{
	e->lem.map.rooms = NULL;
	e->anim.transitions = NULL;
	e->vants = NULL;
	e->anim.static_ants_rooms = NULL;
	e->ant_number = 1;
	e->anim.pause = 0;
	e->time_per_turn = TIME_PER_TURN;
}

void __attribute__((destructor)) end();

void	end(void)
{
//	  ft_printf("destructor loop\n");
//	  while(1);
}

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
	if (e->sdl.ttf_init)
		TTF_Quit();
	if (e->sdl.sdl_init)
		SDL_Quit();
}

int		ft_process_main(char *str, t_env *e)
{
	int ret;

	e->lem.turn++;
	if (!(ret = ft_render_visu(e, str)))
	{
		if (ret == -1)
			ft_printf("malloc error\n");
		ft_strdel(&(str));
		ft_free_all(e);
		return (1);
	}
	ft_strdel(&(str));
	return (0);
}

int		main(void)
{
	t_env	e;
	char	*str;

	ft_init_env(&e);
	if (ft_init_all(&e))
	{
		ft_printf("Initialisation error\n");
		ft_free_all(&e);
		return (1);
	}
	if (ft_parse_visu(&(e.lem)) == -1)
	{
		ft_printf("Parsing error\n");
		ft_free_all(&e);
		return (1);
	}
	ft_gather_stats(&e);
	ft_update_corr_pos(&e);
	e.lem.turn = 0;
	while (get_next_line(0, &str) > 0)
	{
		if (ft_process_main(str, &e))
			return (0);
	}
	ft_strdel(&(str));
	ft_render_visu_end(&e);
	ft_free_all(&e);
	return (0);
}

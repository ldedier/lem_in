/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:51:01 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/19 15:54:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int		ft_render_selected_room(t_env *e)
{
	char		*str;
	SDL_Rect	pos;
	double		scale;

	scale = 10.0 * e->react.w_scale;
	if (!(str = ft_strjoin("room: ", e->selected_room->name)))
		return (1);
	if (ft_use_texture_with_surface(e, str))
		return (1);
	ft_fill_rect_x_y(&pos, (e->dim.width / 2) - (ft_strlen(str) * scale),
		e->react.h_scale * 140);
	ft_fill_rect_w_h(&pos, ft_strlen(str) * 2 * scale, 45 * e->react.h_scale);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &pos);
	SDL_DestroyTexture(e->sdl.texture);
	ft_strdel(&str);
	return (0);
}

int		ft_render_turn(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	int			scale;

	scale = 15.0 * e->react.w_scale;
	if (!(str2 = ft_itoa(e->lem.turn)))
		return (1);
	if (!(str = ft_strjoin("turn #", str2)))
		return (ft_free_turn(str2, 1));
	ft_strdel(&str2);
	ft_fill_rect_x_y(&pos, (e->dim.width / 2) - ft_strlen(str) * scale,
		65 * e->react.h_scale);
	ft_fill_rect_w_h(&pos, ft_strlen(str) * 2 * scale, 70 * e->react.h_scale);
	if (ft_use_texture_with_surface(e, str))
		return (ft_free_turn(str, 1));
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &pos);
	SDL_DestroyTexture(e->sdl.texture);
	ft_strdel(&str);
	return (0);
}

int		ft_render_speed_value(t_env *e)
{
	char		*str;
	char		*str2;
	SDL_Rect	pos;
	int			scale;

	scale = 10.0 * e->react.w_scale;
	if (!(str2 = ft_itoa(e->time_per_turn)))
		return (1);
	if (!(str = ft_strjoin(str2, " ms")))
		return (ft_free_turn(str2, 1));
	ft_strdel(&str2);
	if (ft_use_texture_with_surface(e, str))
		return (ft_free_turn(str, 1));
	ft_fill_rect_x_y(&pos, e->dim.width - ((230.0 / 2560) * e->dim.width) -
		(ft_strlen(str) * scale), 110 * e->react.h_scale);
	ft_fill_rect_w_h(&pos, ft_strlen(str) * 2 * scale, 45 * e->react.h_scale);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &pos);
	SDL_DestroyTexture(e->sdl.texture);
	ft_strdel(&str);
	return (0);
}

int		ft_render_speed(t_env *e)
{
	SDL_Rect	pos;
	int			scale;

	scale = 10.0 * e->react.w_scale;
	if (ft_use_texture_with_surface(e, "time per turn"))
		return (1);
	ft_fill_rect_x_y(&pos, e->dim.width - ((230.0 / 2560) * e->dim.width) -
		(14 * scale), 60 * e->react.h_scale);
	ft_fill_rect_w_h(&pos, 14 * 2 * scale, 45 * e->react.h_scale);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, &pos);
	SDL_DestroyTexture(e->sdl.texture);
	return (ft_render_speed_value(e));
}

int		ft_render_dashboard(t_env *e)
{
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = e->dim.width;
	rect.h = e->react.grass_border;
	SDL_SetRenderDrawColor(e->sdl.renderer, 50, 50, 50, 255);
	SDL_RenderFillRect(e->sdl.renderer, &rect);
	if (ft_render_nb_ants(e))
		return (1);
	if (ft_render_turn(e))
		return (1);
	if (ft_render_speed(e))
		return (1);
	if (e->selected_room != NULL)
	{
		if (ft_render_selected_room(e))
			return (1);
	}
	return (0);
}

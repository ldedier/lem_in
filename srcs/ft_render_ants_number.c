/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_ants_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:57:21 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 12:57:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int		ft_render_nb_ants_rect(SDL_Rect *pos, char *title,
			int value, t_env *e)
{
	char		*str;
	char		*str2;

	if (ft_use_texture_with_surface(e, title))
		return (1);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, pos);
	SDL_DestroyTexture(e->sdl.texture);
	if (!(str2 = ft_itoa(value)))
		return (1);
	if (!(str = ft_strjoin(str2, value == 1 ? " ant" : " ants")))
		return (ft_free_turn(str2, 1));
	ft_strdel(&str2);
	if (ft_use_texture_with_surface(e, str))
		return (ft_free_turn(str, 1));
	pos->x = 250 * e->react.w_scale;
	pos->w = ft_strlen(str) * 20 * e->react.w_scale;
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, pos);
	SDL_DestroyTexture(e->sdl.texture);
	ft_strdel(&str);
	return (0);
}

int		ft_render_nb_ants_start(t_env *e)
{
	SDL_Rect	pos;

	pos.x = 20 * e->react.w_scale;
	pos.y = 20 * e->react.h_scale;
	pos.w = 200 * e->react.w_scale;
	pos.h = 45 * e->react.h_scale;
	return (ft_render_nb_ants_rect(&pos, "beginning:",
		e->lem.map.start->ant_count, e));
}

int		ft_render_nb_ants_end(t_env *e)
{
	SDL_Rect	pos;

	pos.x = 20 * e->react.w_scale;
	pos.y = 80 * e->react.h_scale;
	pos.w = 80 * e->react.w_scale;
	pos.h = 45 * e->react.h_scale;
	return (ft_render_nb_ants_rect(&pos, "end:",
		e->lem.map.end->ant_count - e->toward_end, e));
}

int		ft_render_nb_ants_others(t_env *e)
{
	SDL_Rect	pos;

	pos.x = 20 * e->react.w_scale;
	pos.y = 140 * e->react.h_scale;
	pos.w = 140 * e->react.w_scale;
	pos.h = 45 * e->react.h_scale;
	return (ft_render_nb_ants_rect(&pos, "others:",
		e->lem.map.total_ants - (e->lem.map.start->ant_count +
			(e->lem.map.end->ant_count - e->toward_end)), e));
}

int		ft_render_nb_ants(t_env *e)
{
	if (ft_render_nb_ants_start(e))
		return (1);
	if (ft_render_nb_ants_end(e))
		return (1);
	if (ft_render_nb_ants_others(e))
		return (1);
	return (0);
}

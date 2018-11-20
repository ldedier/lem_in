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

/*
** return the position of moving ant at the very instant
*/

SDL_Rect	ft_get_pos(t_env *e, t_transition *tr)
{
	SDL_Rect res;

	res.w = e->room_size / 2;
	res.h = e->room_size / 2;
	res.x = tr->from->corr_x + ((double)e->room_size / 4) +
		(e->anim.progress) * ((tr->to->corr_x + (e->room_size / 4) -
					(tr->from->corr_x + (e->room_size / 4))));
	res.y = tr->from->corr_y + ((double)e->room_size / 4) +
		(e->anim.progress) * ((tr->to->corr_y + (e->room_size / 4) -
					(tr->from->corr_y + (e->room_size / 4))));
	return (res);
}

int			ft_get_angle(t_env *e, t_transition *tr)
{
	return (((atan2(tr->to->corr_y + e->room_size / 2 -
				(tr->from->corr_y + e->room_size / 2),
				tr->to->corr_x + e->room_size / 2 -
					(tr->from->corr_x + e->room_size / 2)) * 180 / M_PI) + 90));
}

int			ft_dist_transition(t_transition *tr)
{
	return (ft_dist(tr->from->corr_x, tr->from->corr_y,
					tr->to->corr_x, tr->to->corr_y));
}

void	ft_render_ants(t_env *e)
{
	t_list			*ptr;
	t_transition	*tr;
	SDL_Rect		pos;
	SDL_Point		center;
	int				current_animation;

	ptr = e->anim.transitions;
	while (ptr != NULL)
	{
		tr = (t_transition *)(ptr->content);
		tr->angle = ft_get_angle(e, tr);
		pos = ft_get_pos(e, tr);
		center.x = pos.w / 2;
		center.y = pos.h / 2;
		current_animation = (((int)(e->anim.progress * 4 *
				(ft_dist_transition(tr) * 0.025))) % 4);
		SDL_RenderCopyEx(e->sdl.renderer,
				e->sdl.ant_textures[current_animation], NULL, &pos,
					tr->angle, &center, SDL_FLIP_NONE);
		ptr = ptr->next;
	}
}

void	ft_render_static_ants(t_env *e)
{
	t_list		*ptr;
	t_room		*room;
	SDL_Rect	pos;
	SDL_Point	center;

	ptr = e->anim.static_ants_rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		pos.x = room->corr_x + e->room_size / 4;
		pos.y = room->corr_y + e->room_size / 4;
		pos.w = e->room_size / 2;
		pos.h = e->room_size / 2;
		center.x = pos.w / 2;
		center.y = pos.h / 2;
		SDL_RenderCopyEx(e->sdl.renderer, e->sdl.textures[ANT],
			NULL, &pos, 0, &center, SDL_FLIP_NONE);
		ptr = ptr->next;
	}
}

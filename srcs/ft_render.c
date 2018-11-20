/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:51:01 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 15:46:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int		ft_render(t_env *e)
{
	SDL_SetRenderDrawColor(e->sdl.renderer, 100, 100, 100, 255);
	SDL_RenderClear(e->sdl.renderer);
	if (ft_render_dashboard(e))
		return (1);
	ft_render_links(e);
	ft_render_rooms(e);
	ft_render_ants(e);
	ft_render_static_ants(e);
	SDL_RenderPresent(e->sdl.renderer);
	return (0);
}

int		ft_add_current_ants(t_env *e, char *str)
{
	int ret;

	if ((ret = ft_add_transitions(e, str)))
	{
		ft_lstdel_value(&(e->anim.transitions));
		ft_lstdel_ptr(&(e->anim.static_ants_rooms));
		return (ret);
	}
	if (ft_add_static(e))
	{
		ft_lstdel_value(&(e->anim.transitions));
		ft_lstdel_ptr(&(e->anim.static_ants_rooms));
		return (-1);
	}
	return (0);
}

int		ft_render_visu(t_env *e, char *str)
{
	int			loop;
	int			ret;

	e->toward_end = 0;
	if ((ret = ft_add_current_ants(e, str)))
		return (ret);
	e->anim.start = SDL_GetTicks();
	e->anim.previous = e->anim.start;
	e->anim.progress = 0;
	loop = 1;
	while (loop == 1 && e->anim.progress < 1)
		ft_process_current_turn(e, &loop);
	ft_lstdel_value(&(e->anim.transitions));
	ft_lstdel_ptr(&(e->anim.static_ants_rooms));
	return (loop);
}

int		ft_render_visu_end(t_env *e)
{
	int loop;

	e->toward_end = 0;
	loop = 1;
	while (loop)
	{
		ft_process_end_events(e, &loop);
		ft_process_end(e);
		if (ft_render(e))
			return (1);
		SDL_Delay(20);
	}
	return (0);
}

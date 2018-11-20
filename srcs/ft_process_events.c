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

void		ft_process_current_turn(t_env *e, int *loop)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN &&
					event.key.keysym.sym == SDLK_ESCAPE))
			*loop = 0;
		else if (event.type == SDL_KEYDOWN && !event.key.repeat)
			ft_key_down(e, event.key.keysym.sym);
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			ft_mouse_down(e, event);
		else if (event.type == SDL_MOUSEBUTTONUP)
			ft_mouse_up(e, event);
		else if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(e, event);
	}
	if (!e->anim.pause)
		ft_process_animation(e);
	ft_process(e, SDL_GetKeyboardState(NULL));
	if (ft_render(e))
		*loop = -1;
	SDL_Delay(20);
}

void	ft_process_end_events(t_env *e, int *loop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN &&
					event.key.keysym.sym == SDLK_ESCAPE))
			*loop = 0;
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			ft_mouse_down(e, event);
		else if (event.type == SDL_MOUSEBUTTONUP)
			ft_mouse_up(e, event);
		else if (event.type == SDL_MOUSEMOTION)
			ft_mouse_motion(e, event);
		else if (event.type == SDL_KEYDOWN &&
				event.key.keysym.sym == SDLK_r)
			ft_reset_pos(e);
	}
}

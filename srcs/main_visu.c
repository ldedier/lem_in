/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/12 19:11:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void ft_render(t_env *e)
{
	SDL_RenderCopy(e->sdl.renderer, e->sdl.textures[BACKGROUND], NULL, NULL);
//	SDL_RenderCopyEx(e->renderer, e->sdl.textures[ANT], NULL, &playerPos, angle, &center, SDL_FLIP_NONE);
	SDL_RenderPresent(e->sdl.renderer);
}

void RunGame(t_env *e)
{
	int loop;
	SDL_Event event;

	loop = 1;
	while (loop)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || 
			(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				loop = 0;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_RIGHT:
						break;
					case SDLK_LEFT:
						break;
					case SDLK_DOWN:
						break;
					case SDLK_UP:
						break;
					default :
						break;
				}
			}
		}
		ft_render(e);
		SDL_Delay(16);
	}
}

int main()
{
	t_env e;

	if (!ft_init_all(&e))
	{
		ft_printf("visu initialisation error\n");
		return (-1);
	}
	SDL_RenderCopy(e.sdl.renderer, e.sdl.textures[BACKGROUND], NULL, NULL);
	RunGame(&e);
	return (0);
}

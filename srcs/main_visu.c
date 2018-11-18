/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/18 18:34:30 by ldedier          ###   ########.fr       */
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

void    end(void)
{
//	  ft_printf("destructor loop\n");
//	  while(1);
}


void	ft_free_textures(t_env *e)
{
	int i;

	i = 0;
	while (i < 8)
	{
		SDL_DestroyTexture(e->sdl.textures[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		SDL_DestroyTexture(e->sdl.ant_textures[i]);
		i++;
	}
}

void	ft_free_all(t_env *e)
{
	ft_lstdel_value(&(e->vants));
	ft_delete_rooms(&(e->lem.map.rooms));
	ft_free_textures(e);
	TTF_CloseFont(e->sdl.font);
	SDL_FreeSurface(e->sdl.w_surface);
	SDL_DestroyRenderer(e->sdl.renderer);
	SDL_DestroyWindow(e->sdl.window);
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

int main(int argc, char **argv)
{
	t_env	e;
	char	*str;

	(void) argc;
	(void) argv;
	ft_init_env(&e);
	if (!ft_init_all(&e))
		ft_error("Initialisation error\n");
	if (ft_parse_visu(&(e.lem)) == -1)
		ft_error("Parsing error\n");
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

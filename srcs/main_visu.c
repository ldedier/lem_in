/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 17:33:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_init_env(t_env *e)
{
	e->lem.map.rooms = NULL;
	e->lem.turn = 0;
	e->lem.verbosed = 0;
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
	  ft_printf("destructor loop\n");
	  while(1);
}

void	ft_print_error(int error)
{
	if (error == -1)
		ft_printf("malloc error\n");
	else if (error == -2)
		ft_printf("error: empty transition line !\n");
	else if (error == -3)
		ft_printf("error: ant is jumping to an unlinked room !\n");
	else if (error == -4)
		ft_printf("error: wrong transition syntax (L1-room_name) !\n");
	else if (error == -5)
		ft_printf("error: wrong ant new id !\n");
}

int		ft_process_main(char *str, t_env *e)
{
	int ret;

	e->lem.turn++;
	if (!(ret = ft_render_visu(e, str)))
	{
		ft_strdel(&(str));
		ft_free_all(e);
		return (1);
	}
	else if (ret != 1)
	{
		ft_print_error(ret);
		ft_strdel(&(str));
		ft_free_all(e);
		return (-1);
	}
	ft_strdel(&(str));
	return (0);
}

int		ft_prepare_visu(t_env *e)
{
	ft_init_sdl_to_null(e);
	ft_init_textures_to_null(e);
	e->sdl.font = NULL;
	if (ft_parse_visu(&(e->lem)) == -1)
	{
		ft_printf("Parsing error\n");
		ft_free_all(e);
		return (1);
	}
	if (ft_init_all_sdl(e))
	{
		ft_printf("Initialisation error\n");
		ft_free_all(e);
		return (1);
	}
	ft_gather_stats(e);
	ft_update_corr_pos(e);
	return (0);
}

int		main(void)
{
	t_env	e;
	char	*str;
	int		ret;

	ft_init_env(&e);
	if (ft_prepare_visu(&e))
		return (1);
	while (get_next_line(0, &str) > 0)
	{
		if ((ret = ft_process_main(str, &e)))
			return (ret == -1 ? 1 : 0);
	}
	ft_strdel(&(str));
	if (ft_render_visu_end(&e))
	{
		ft_printf("malloc error\n");
		return (1);
	}
	ft_free_all(&e);
	return (0);
}

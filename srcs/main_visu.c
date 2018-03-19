/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/19 16:48:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int main(int argc, char **argv)
{
	t_env e;
	char *str;

	(void)argc;
	(void)argv;
	e.lem.map.rooms = NULL;
	e.anim.transitions = NULL;
	e.anim.static_ants_rooms = NULL;
	e.anim.pause = 0;
	e.keys.can_pause = 1;
	e.time_per_turn = TIME_PER_TURN;
	if (!ft_init_all(&e))
		ft_error("Initialisation error\n");
	if (ft_parse_visu(&(e.lem)) == -1)
		ft_error("Parsing error\n");
	//	ft_affich_map(&(e.lem.map));
	ft_gather_stats(&e);
	ft_update_corr_pos(&e);
//	ft_debug_stats(&(e.stats));
	while (get_next_line(0, &str) > 0)
	{
		ft_render_visu(&e, str);
//		ft_update_map(&(e.lem.map), str);
//		ft_affich_map(&(e.lem.map));
		e.anim.transitions = NULL;
		e.anim.static_ants_rooms = NULL;
		//TO FREE
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/07/07 22:58:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_init_env(t_env *e)
{
	e->lem.map.rooms = NULL;
	e->anim.transitions = NULL;
	e->anim.static_ants_rooms = NULL;
	e->anim.pause = 0;
	e->keys.can_pause = 1;
	e->time_per_turn = TIME_PER_TURN;
	e->reversed = 0;
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
		e.lem.turn++;
		ft_render_visu(&e, str);
		e.anim.transitions = NULL;
		e.anim.static_ants_rooms = NULL;
		//TO FREE
	}
	ft_render_visu_end(&e);
	return (0);
}

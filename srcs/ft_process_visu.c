/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/16 18:14:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_process(t_env *e, const Uint8 *keys)
{
	if (keys[SDL_SCANCODE_UP])
	{
		if (e->time_per_turn > 100)
			e->time_per_turn -= 100;
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		if (e->time_per_turn < 10000)
			e->time_per_turn += 100;
	}
}

void	ft_process_end(t_env *e)
{
	(void)e;
}

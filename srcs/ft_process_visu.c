/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/02 12:53:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_process(t_env *e)
{
	if (e->keys.up && e->time_per_turn > 100)
	{
		e->time_per_turn -= 100;
	}
	if (e->keys.down)
	{
		e->time_per_turn += 100;
	}
}

void	ft_process_end(t_env *e)
{
	(void)e;
}

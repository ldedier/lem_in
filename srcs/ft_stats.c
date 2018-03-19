/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 03:03:57 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/19 03:03:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_update_stats(t_room *room, t_env *e)
{
	if (room->x < e->stats.left || !e->stats.left_fix)
	{
		e->stats.left = room->x;
		e->stats.left_fix = 1;
	}
	if (room->x > e->stats.right || !e->stats.right_fix)
	{
		e->stats.right = room->x;
		e->stats.right_fix = 1;
	}
	if (room->y > e->stats.bottom || !e->stats.bottom_fix)
	{
		e->stats.bottom = room->y;
		e->stats.bottom_fix = 1;
	}
	if (room->y < e->stats.top || !e->stats.top_fix)
	{
		e->stats.top = room->y;
		e->stats.top_fix = 1;
	}
}

void	ft_gather_stats(t_env *e)
{
	t_list *ptr;
	t_room *room;

	ptr = e->lem.map.rooms;
	e->stats.top_fix = 0;
	e->stats.bottom_fix = 0;
	e->stats.right_fix = 0;
	e->stats.left_fix = 0;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		ft_update_stats(room, e);
		ptr = ptr->next;
	}
}

void	ft_debug_stats(t_stats* stats)
{
	ft_printf("top:%d\n", stats->top);
	ft_printf("bottom:%d\n", stats->bottom);
	ft_printf("left:%d\n", stats->left);
	ft_printf("right:%d\n", stats->right);
}

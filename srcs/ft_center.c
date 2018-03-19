/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_center.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 02:54:59 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/19 02:55:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int		ft_iz_okay(t_env *e)
{
	double w_alpha;
	double h_alpha;
	t_list *ptr;
	t_list *ptr2;
	t_room *room;
	t_room *room2;

	ptr = e->lem.map.rooms;
	w_alpha = (double)((double)(9.0 * e->dim.width) / ((double)(10.0 * ((double)e->stats.right - e->stats.left)))) - (double)e->room_size / (double)(e->stats.right - e->stats.left);
	h_alpha = (double)((9.0 * (e->dim.height - GRASS_BORDER)) / ((double)(10.0 * ((double)e->stats.bottom - e->stats.top)))) - (double)e->room_size / (double)(e->stats.bottom - e->stats.top);

	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		ptr2 = e->lem.map.rooms;
		while (ptr2 != NULL)
		{
			room2 = (t_room *)(ptr2->content);
			if (room != room2 && sqrt(pow(room->x * w_alpha - room2->x * w_alpha, 2) + pow(room->y * h_alpha - room2->y * h_alpha, 2)) <= e->room_size)
				return (0);
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return (1);
}

void	ft_update_room_size(t_env *e)
{
	e->room_size = ROOM_SIZE;
	while (!ft_iz_okay(e))
		e->room_size -= 10;
}

void	ft_update_corr_pos(t_env *e)
{
	double w_alpha;
	double h_alpha;
	t_list *ptr;
	t_room *room;
	int x_margin;
	int y_margin;

	ptr = e->lem.map.rooms;
	ft_update_room_size(e);
	w_alpha = (double)((double)(9.0 * e->dim.width) / ((double)(10.0 * ((double)e->stats.right - e->stats.left)))) - (double)e->room_size / (double)(e->stats.right - e->stats.left);
	h_alpha = (double)((9.0 * (e->dim.height - GRASS_BORDER)) / ((double)(10.0 * ((double)e->stats.bottom - e->stats.top)))) - (double)e->room_size / (double)(e->stats.bottom - e->stats.top);

	x_margin = (e->dim.width / 20) - (e->stats.left * w_alpha);
	y_margin = ((e->dim.height - GRASS_BORDER) / 20) - (e->stats.top * h_alpha) + GRASS_BORDER;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		room->corr_x_init = x_margin + room->x * w_alpha;
		room->corr_y_init = y_margin + room->y * h_alpha;
		room->corr_x = room->corr_x_init;
		room->corr_y = room->corr_y_init;
		ptr = ptr->next;
	}
}

int	ft_dist(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

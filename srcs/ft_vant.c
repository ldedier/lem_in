/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:09:26 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 21:31:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

t_vant	*ft_new_vant(int id, t_room *room)
{
	t_vant	*vant;

	if (!(vant = (t_vant *)malloc(sizeof(t_vant))))
		return (NULL);
	vant->id = id;
	vant->room = room;
	return (vant);
}

int		ft_update_ant(t_vant *vant, t_room *to, t_env *e)
{
	t_transition	*transition;

	if (!ft_already_in_transitions(e->anim.transitions,
				vant->room, to))
	{
		if (!(transition = ft_new_transition(vant->room, to)))
			return (-1);
		ft_apply_transition(e, vant->room, to);
		if (ft_add_to_list_ptr(&(e->anim.transitions),
					transition, sizeof(t_transition)))
		{
			free(transition);
			return (-1);
		}
		vant->room = to;
		if (vant->room == e->lem.map.end)
			return (1);
	}
	else
		ft_apply_transition(e, vant->room, to);
	return (0);
}

int		ft_create_ant_to(int id, char *room_name, t_env *e)
{
	t_room			*to;
	t_vant			*vant;
	static int		i = 1;

	if (id != i++)
		return (-5);
	if (!(to = ft_get_neighbour(e->lem.map.start, room_name)))
		return (-3);
	if (!(vant = ft_new_vant(id, to)))
		return (-1);
	if (!ft_already_in_transitions(e->anim.transitions, e->lem.map.start, to))
	{
		if (ft_process_ant_transition(vant, to, e))
			return (-1);
	}
	else
		ft_apply_transition(e, e->lem.map.start, to);
	if (to == e->lem.map.end ||
			ft_add_to_list_ptr(&(e->vants), vant, sizeof(t_vant)))
	{
		free(vant);
		return (to == e->lem.map.end ? 0 : -1);
	}
	return (0);
}

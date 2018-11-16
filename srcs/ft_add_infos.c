/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/16 16:26:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int		ft_add_static(t_env *e)
{
	e->anim.static_ants_rooms = NULL;
	t_list *ptr;
	t_list *ptr2;
	t_room *room;
	t_transition *tr;
	int is_static_ant;

	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (room->ant_count && room != e->lem.map.start && room != e->lem.map.end)
		{
			is_static_ant = 1;
			ptr2 = e->anim.transitions;
			while (ptr2 != NULL)
			{
				tr = (t_transition *)(ptr2->content);
				if (tr->to == room)
				{
					is_static_ant = 0;
					break;
				}
				ptr2 = ptr2->next;
			}
			if (is_static_ant)
			{
				if (ft_add_to_list_ptr(&(e->anim.static_ants_rooms), room, sizeof(t_room)))
					return (1);
			}
		}
		ptr = ptr->next;
	}
	return (0);
}

void		ft_apply_transition(t_env *e, t_room *from, t_room *to)
{
	if (to == e->lem.map.end)
		e->toward_end++;
	from->ant_count--;
	to->ant_count++;
}

t_transition *ft_new_transition(t_room *from, t_room *to)
{
	t_transition *res;

	res = (t_transition *)(malloc(sizeof(t_transition)));
	res->from = from;
	res->to = to;
	return (res);
}

t_room	*ft_get_neighbour(t_room *room, char *room_name)
{
	t_list	*ptr;
	t_room *neighbour;

	ptr = room->neighbours;
	while (ptr != NULL)
	{
		neighbour = (t_room *)(ptr->content);
		if (!ft_strcmp(neighbour->name, room_name))
			return (neighbour);
		ptr = ptr->next;
	}
	return (NULL);
}

int		ft_already_in_transitions(t_list *transitions, t_room *from, t_room *to)
{
	t_list *ptr;
	t_transition *transition;

	ptr = transitions;
	while (ptr != NULL)
	{
		transition = (t_transition *)(ptr->content);
		if (from == transition->from && to == transition->to)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}


t_vant	*ft_new_vant(int id, t_room *room)
{
	t_vant	*vant;

	if (!(vant = (t_vant *)malloc(sizeof(t_vant))))
		return (NULL);
	vant->id = id;
	vant->room = room;
	return (vant);
}

int		ft_add_transition(t_env *e, int id, char *room_name)
{
	t_list			*ptr;
	t_vant			*vant;
	t_transition	*transition;
	t_room			*room;

	ptr = e->vants;
	while (ptr != NULL)
	{
		vant = (t_vant *)(ptr->content);
		if (vant->id == id)
		{
			if (!(room = ft_get_neighbour(vant->room, room_name)))
				return (1);
			if (!ft_already_in_transitions(e->anim.transitions, vant->room, room))
			{
				transition = ft_new_transition(vant->room, room);
				ft_apply_transition(e, vant->room, room);
				if (ft_add_to_list_ptr(&(e->anim.transitions),
					transition, sizeof(t_transition)))
				return (1);
				vant->room = room;
			}
			else
				ft_apply_transition(e, vant->room, room);
			return (0);
		}
		ptr = ptr->next;
	}
	if (!(room = ft_get_neighbour(e->lem.map.start, room_name)))
		return (1);
	if (!(vant = ft_new_vant(id, room)))
		return (1);
	if (!ft_already_in_transitions(e->anim.transitions, e->lem.map.start, room))
	{
		transition = ft_new_transition(e->lem.map.start, room);
		ft_apply_transition(e, e->lem.map.start, room);
		vant->room = room;
		if (ft_add_to_list_ptr(&(e->anim.transitions),
					transition, sizeof(t_transition)))
			return (1);
	}
	else
		ft_apply_transition(e, e->lem.map.start, room);
	if (ft_add_to_list_ptr(&(e->vants),
					vant, sizeof(t_vant)))
				return (1);

	return (0);
}

void	ft_add_transitions(t_env *e, char *str)
{
	char	**split;
	int		i;
	char	**ant_split;

	i = 0;
	split = ft_strsplit(str, ' ');
	while (split[i])
	{
		ant_split = ft_strsplit(split[i], '-');
		ft_add_transition(e, ft_atoi(&(ant_split[0][1])), ant_split[1]);
		ft_free_split(ant_split);
		i++;
	}
	ft_free_split(split);
}

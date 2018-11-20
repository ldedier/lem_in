/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_add_visu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:04:40 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 15:20:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

int		ft_add_static(t_env *e)
{
	t_list	*ptr;
	t_room	*room;

	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (room->ant_count && room != e->lem.map.start &&
				room != e->lem.map.end)
		{
			if (!ft_get_transition_to(e->anim.transitions, room))
			{
				if (ft_add_to_list_ptr(&(e->anim.static_ants_rooms),
						room, sizeof(t_room)))
					return (1);
			}
		}
		ptr = ptr->next;
	}
	return (0);
}

int		ft_add_transition(t_env *e, int id, char *room_name)
{
	t_list			*ptr;
	t_list			*prev;
	t_room			*to;
	int				ret;

	prev = NULL;
	ptr = e->vants;
	while (ptr != NULL)
	{
		if (((t_vant *)ptr->content)->id == id)
		{
			if (!(to = ft_get_neighbour(((t_vant *)ptr->content)->room,
					room_name)))
				return (-3);
			if (((ret = (ft_update_ant((t_vant *)(ptr->content), to, e))) == 1))
				return (ft_delete_node(&prev, &ptr, e->vants));
			else
				return (ret);
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (ft_create_ant_to(id, room_name, e));
}

int		ft_add_transitions(t_env *e, char *str)
{
	char	**split;
	int		i;
	char	**ant_split;
	int		ret;

	i = 0;
	split = ft_strsplit(str, ' ');
	if (ft_splitlen(split) == 0)
		return (ft_free_turn_split(split, -2));
	while (split[i])
	{
		ant_split = ft_strsplit(split[i], '-');
		if (ft_splitlen(ant_split) == 2 && ft_strlen(ant_split[0]) > 1)
		{
			if ((ret = ft_add_transition(e, ft_atoi(&(ant_split[0][1])),
					ant_split[1])))
				return (ft_free_turn_splits(ant_split, split, ret));
		}
		else
			return (ft_free_turn_splits(ant_split, split, -4));
		ft_free_split(ant_split);
		i++;
	}
	ft_free_split(split);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:35:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/18 17:18:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_init_ant_room(t_room *room, int role, t_lem *lem)
{
	room->ant_count = 0;
	room->neighbours = NULL;
	room->parsed = 0;
	if (role == START)
	{
		room->ant_count = lem->map.total_ants;
		lem->map.start = room;
	}
	else if (role == END)
		lem->map.end = room;
}

t_room 	*ft_new_room_from_split(char **split)
{
	t_room *room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	if (!(room->name = ft_strdup(split[0])))
	{
		free(room);
		return (NULL);
	}
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	return (room);
}

int		ft_process_add_room(char **split, t_lem *lem, int role)
{
	t_room	*room;

	if (!(room = ft_new_room_from_split(split)))
	{
		ft_free_split(split);
		return (-1);
	}
	if (ft_add_to_list_ptr(&(lem->map.rooms), room, sizeof(t_room)))
	{
		free(room->name);
		free(room);
		ft_free_split(split);
		return (-1);
	}
	ft_init_ant_room(room, role, lem);
	lem->parser.phase = e_phase_rooms;
	ft_free_split(split);
	return (0);

}

int		ft_add_room(char *str, t_lem *lem, int role)
{
	char	**split;

	if (!(split = ft_strsplit(str, ' ')))
		return (-1);
	if (ft_is_valid_room(split, lem))
		return (ft_process_add_room(split, lem, role));
	else
	{
		ft_free_split(split);
		ft_verbose(lem, str, "invalid room");
		return (-1);
	}
}

t_room	*ft_get_room(t_list *rooms, char *str)
{
	while (rooms != NULL)
	{
		if (!ft_strcmp(((t_room *)(rooms->content))->name, str))
			return ((t_room *)(rooms->content));
		rooms = rooms->next;
	}
	return (NULL);
}

int		ft_not_linked_yet(t_room *r1, t_room *r2)
{
	t_list *ptr;

	ptr = r1->neighbours;
	while (ptr != NULL)
	{
		if (((t_room *)(ptr->content)) == r2)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

int		ft_process_add_link(t_room *r1, t_room *r2, char *str, t_lem *lem)
{
	if (r1 && r2)
	{
		if (ft_not_linked_yet(r1, r2))
		{
			if (ft_add_to_list_ptr(&(r1->neighbours), r2, sizeof(t_room)))
				return (-1);
			if (ft_add_to_list_ptr(&(r2->neighbours), r1, sizeof(t_room)))
				return (-1);
		}
		return (1);
	}
	else
	{
		ft_verbose(lem, str, "invalid room name");
		return (-1);
	}
}

int		ft_add_link(char *str, t_lem *lem)
{
	t_room	*r1;
	t_room	*r2;
	char	**split;

	split = ft_strsplit(str, '-');
	if (ft_splitlen(split) == 2)
	{
		r1 = ft_get_room((lem->map.rooms), split[0]);
		r2 = ft_get_room((lem->map.rooms), split[1]);
	}
	else
	{
		ft_free_split(split);
		ft_verbose(lem, str, "invalid link");
		return (-1);
	}
	ft_free_split(split);
	return (ft_process_add_link(r1, r2, str, lem));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:38:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 18:34:00 by ldedier          ###   ########.fr       */
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

t_room	*ft_new_room_from_split(char **split)
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

int		ft_add_role(int role, t_lem *lem)
{
	if (role == START && ++lem->parser.nb_start > 1)
		return (ft_verbose_no_line(lem, "map can only have one start"));
	else if (role == END && ++lem->parser.nb_end > 1)
		return (ft_verbose_no_line(lem, "map can only have one end"));
	return (0);
}

int		ft_process_add_room(char **split, t_lem *lem, int role)
{
	t_room	*room;

	if (ft_add_role(role, lem))
		return (-1);
	if (!(room = ft_new_room_from_split(split)))
	{
		ft_printf("OUAI\n");
		ft_free_split(split);
		return (-2);
	}
	if (ft_add_to_list_ptr(&(lem->map.rooms), room, sizeof(t_room)))
	{
		free(room->name);
		free(room);
		ft_free_split(split);
		return (-2);
	}
	ft_init_ant_room(room, role, lem);
	lem->parser.phase = e_phase_rooms;
	ft_free_split(split);
	return (1);
}

int		ft_add_room(char *str, t_lem *lem, int role)
{
	char	**split;

	if (!(split = ft_strsplit(str, ' ')))
		return (-2);
	if (ft_is_valid_room(split, lem))
		return (ft_process_add_room(split, lem, role));
	else
	{
		ft_free_split(split);
		ft_verbose(lem, str, "invalid room");
		return (-1);
	}
}

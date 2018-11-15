/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:35:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/15 14:06:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_init_ant_room(t_room *room)
{
	room->ant_number = 0;
	room->ant_count = 0;
	room->neighbours = NULL;
	room->parsed = 0;
}

int		ft_free_turn_split(char **split, int ret)
{
	ft_free_split(split);
	return (ret);
}

int		ft_add_room(char *str, t_lem *lem, int role)
{
	char	**split;
	t_room	*room;

	if (!(split = ft_strsplit(str, ' ')))
		return (-1);
	if (ft_is_valid_room(split, lem))
	{
		if (!(room = (t_room *)malloc(sizeof(t_room))))
			return (ft_free_turn_split(split, -1));
		room->name = ft_strdup(split[0]);
		room->x = ft_atoi(split[1]);
		room->y = ft_atoi(split[2]);
		ft_init_ant_room(room);
		if (ft_add_to_list_ptr(&(lem->map.rooms), room, sizeof(t_room)))
		{
			ft_free_split(split);
			free(room);
			return (-1);
		}
		if (role == START)
		{
			room->ant_number = 1;
			room->ant_count = lem->map.total_ants;
			lem->map.start = room;
		}
		else if (role == END)
			lem->map.end = room;
		lem->parser.phase = e_phase_rooms;
		ft_free_split(split);
		return (0);
	}
	else
	{
		ft_printf("ROOM ERROR\n");
		ft_free_split(split);
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

int		ft_add_link(char *str, t_lem *lem)
{
	t_room	*r1;
	t_room	*r2;
	char	**split;

	split = ft_strsplit(str, '-');
	r1 = ft_get_room((lem->map.rooms), split[0]);
	r2 = ft_get_room((lem->map.rooms), split[1]);
	ft_free_split(split);
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
		return (-1);
}

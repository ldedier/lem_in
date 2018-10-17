/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:35:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/23 17:53:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_init_ant_room(t_room *room)
{
	room->ant_number = 0;
	room->ant_count = 0;
	room->neighbours = NULL;
}

int		ft_add_room(char *str, t_lem *lem, int role)
{
	char	**split;
	t_room	*room;

	split = ft_strsplit(str, ' ');
	if (ft_is_valid_room(split, lem))
	{
		room = malloc(sizeof(t_room));
		room->name = ft_strdup(split[0]);
		room->x = ft_atoi(split[1]);
		room->y = ft_atoi(split[2]);
		ft_init_ant_room(room);
		ft_lstadd(&(lem->map.rooms), ft_lstnew_ptr(room, sizeof(t_room)));
		if (role == START)
		{
			room->ant_number = 1;
			room->ant_count = lem->map.total_ants;
			lem->map.start = room;
		}
		else if (role == END)
			lem->map.end = room;
		lem->parser.phase = e_phase_rooms;
		return (0);
	}
	else
	{
		ft_printf("ROOM ERROR\n");
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
	if (r1 && r2)
	{
		if (ft_not_linked_yet(r1, r2))
		{
			ft_lstadd(&(r1->neighbours), ft_lstnew_ptr(r2, sizeof(t_room)));
			ft_lstadd(&(r2->neighbours), ft_lstnew_ptr(r1, sizeof(t_room)));
		}
		return (1);
	}
	else
		return (-1);
}

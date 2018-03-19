/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 03:06:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/19 03:06:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_update_room(t_map *map, int ant_num, char *room_name)
{
	t_list *ptr;
	t_room *room;

	ptr = map->rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (room->ant_number == ant_num)
		{
			room->ant_count--;
			if (room == map->start)
			{
				if (room->ant_count == 0)
					room->ant_number = 0;
				else
					room->ant_number++;
			}
			else
				room->ant_number = 0;
		}
		if (!ft_strcmp(room_name, room->name))
		{
			room->ant_count++;
			room->ant_number = ant_num;
		}
		ptr = ptr->next;
	}
}

void	ft_update_map(t_map *map, char *str)
{
	char **split;
	char **ant_split;
	int i;

	(void)map;
	i = 0;
	split = ft_strsplit(str, ' ');
	while (split[i])
	{
		ant_split = ft_strsplit(split[i], '-');
//		ft_printf("num ant: %d\n", ft_atoi(&(ant_split[0][1])));
//		ft_printf("name room: %s\n\n", ant_split[1]);
		ft_update_room(map, ft_atoi(&(ant_split[0][1])), ant_split[1]);
		i++;

	}
	ft_printf("%s\n", str);
}

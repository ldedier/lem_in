/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solvable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 13:51:01 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/19 12:59:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_process_solve(t_room *current, t_map *map,
			t_list **queue)
{
	t_list *ptr;
	t_room *neighbour;

	ptr = current->neighbours;
	current->parsed = 1;
	while (ptr != NULL)
	{
		neighbour = (t_room *)(ptr->content);
		if (neighbour->parsed == 0)
		{
			neighbour->dist = current->dist + 1;
			if (neighbour == map->end)
				map->is_solvable = 1;
			if (ft_add_to_list_ptr_back(queue, neighbour, sizeof(t_room)))
				return (-1);
		}
		ptr = ptr->next;
	}
	return (0);
}

void	ft_reset_pathfinding(t_map *map)
{
	t_list *ptr;

	ptr = map->rooms;
	while (ptr != NULL)
	{
		((t_room *)(ptr->content))->parsed = 0;
		ptr = ptr->next;
	}
}

int		ft_is_solvable(t_map *map)
{
	t_list	*queue;
	t_room	*current;
	int		ret;

	queue = NULL;
	ft_reset_pathfinding(map);
	map->start->dist = 0;
	if (ft_add_to_list_ptr_back(&queue, map->start, sizeof(t_room)))
		return (-1);
	while (queue != NULL)
	{
		current = (t_room *)(ft_lstpop_ptr(&queue));
		if ((ret = ft_process_solve(current, map, &queue)))
		{
			ft_lstdel_ptr(&queue);
			return (-1);
		}
	}
	return (map->is_solvable);
}

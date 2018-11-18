/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solvable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 13:51:01 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/18 17:00:42 by ldedier          ###   ########.fr       */
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
			if (neighbour == map->end)
				return (1);
			else if (ft_add_to_list_ptr_back(queue, neighbour, sizeof(t_room)))
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
	if (ft_add_to_list_ptr_back(&queue, map->start, sizeof(t_room)))
		return (-1);
	while (queue != NULL)
	{
		current = (t_room *)(ft_lstpop_ptr(&queue));
		if ((ret = ft_process_solve(current, map, &queue)))
		{
			ft_lstdel_ptr(&queue);
			return (ret);
		}
	}
	return (0);
}

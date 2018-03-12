/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_lem_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:40:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/12 17:36:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


void	ft_process_room(t_room *current, t_map *map, t_list **queue)
{
	t_list *ptr;
	t_room *neighbour;

	ptr = current->neighbours;
	current->parsed = 1;
	while (ptr != NULL)
	{
		neighbour = (t_room *)(ptr->content);
		if (neighbour->parsed == 0 || neighbour == map->start)
		{
		//	if(neighbour->parsed != 0 && neighbour == map->start)
		//		ft_printf("WOOOOOOOO %s\n", current->name);
		//	ft_printf("%s\n", neighbour->name);
			if ((current->ant_count == 0 || current == map->end) &&
				(neighbour->ant_count))
			{
				current->ant_count++;
				neighbour->ant_count--;
				if (neighbour == map->start)
					current->ant_number = neighbour->ant_number++;
				else
					current->ant_number = neighbour->ant_number;
				ft_printf("L%d-%s ",current->ant_number, current->name);
			}
			ft_lstpushback(queue, ft_lstnew_ptr(neighbour, sizeof(t_room)));
		}
		ptr = ptr->next;
	}
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

/*
** find the optimal ants movement for each turn and write it on standard output
*/
int		ft_process_lem_in(t_map *map)
{
	t_list *queue;
	t_room *current;

	queue = NULL;
	while (map->end->ant_count != map->total_ants)
	{
		ft_reset_pathfinding(map);
		ft_lstadd(&queue, ft_lstnew_ptr(map->end, sizeof(t_room)));
	//	ft_affich_queue(queue);
		while (queue != NULL)
		{
			current = (t_room *)(ft_lstpop(&queue));
		//	ft_affich_queue(queue);
		//	sleep(1);
			ft_process_room(current, map, &queue);
		}
		ft_printf("\n");
		//ft_printf("%d\n", map->end->ant_count);
	}
	return (0);
}

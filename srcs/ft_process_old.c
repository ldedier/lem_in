/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_lem_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 21:15:55 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/02 14:25:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_print_transition(t_room *current, int *first)
{
	if (*first == 0)
		ft_printf(" L%d-%s",current->ant_number, current->name);
	else
	{
		*first = 0;
		ft_printf("L%d-%s",current->ant_number, current->name);
	}
}

t_list	*ft_list_at(t_list *begin_list, unsigned int n)
{
	unsigned int	i;
	t_list			*list_ptr;

	i = 0;
	list_ptr = begin_list;
	while (list_ptr != NULL && i < n)
	{
		list_ptr = list_ptr->next;
		i++;
	}
	return (list_ptr);
}

int		ft_list_size(t_list *begin_list)
{
	int		i;
	t_list	*list_ptr;

	i = 0;
	list_ptr = begin_list;
	while (list_ptr != NULL)
	{
		i++;
		list_ptr = list_ptr->next;
	}
	return (i);
}

void	ft_list_reverse(t_list *begin_list)
{
	int		i;
	int		len;
	void	*tmp;

	i = 0;
	len = ft_list_size(begin_list);
	if (len < 2)
		return ;
	while (i < len / 2)
	{
		tmp = ft_list_at(begin_list, i)->content;
		ft_list_at(begin_list, i)->content =
			ft_list_at(begin_list, len - i - 1)->content;
		ft_list_at(begin_list, len - i - 1)->content = tmp;
		i++;
	}
}

void	ft_process_room(t_room *current, t_map *map, t_list **queue, int *first)
{
	t_list *ptr;
	t_room *neighbour;

	ptr = current->neighbours;
	current->parsed = 1;
	while (ptr != NULL)
	{
		if (rand() % 2 == 0)
		{
			ft_list_reverse(ptr);
		}
		neighbour = (t_room *)(ptr->content);
		if (neighbour->parsed == 0 || neighbour == map->start)
		{
			if ((current->ant_count == 0 || current == map->end) &&
					(neighbour->ant_count))
			{
				current->ant_count++;
				neighbour->ant_count--;
				if (neighbour == map->start)
					current->ant_number = neighbour->ant_number++;
				else
					current->ant_number = neighbour->ant_number;
				ft_print_transition(current, first);
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
	t_listwye *queue;
	t_room *current;
	int first;

	queue = NULL;
	while (map->end->ant_count != map->total_ants)
	{
		first = 1;
		ft_reset_pathfinding(map);
		ft_lstadd(&queue, ft_lstnew_ptr(map->end, sizeof(t_room)));
		while (queue != NULL)
		{
			current = (t_room *)(ft_lstpop(&queue));
			ft_process_room(current, map, &queue, &first);
		}
		ft_printf("\n");
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/07/07 22:49:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_add_static(t_env *e)
{
	e->anim.static_ants_rooms = NULL;
	t_list *ptr;
	t_list *ptr2;
	t_room *room;
	t_transition *tr;
	int is_static_ant;

	ptr = e->lem.map.rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		if (room->ant_count && room != e->lem.map.start && room != e->lem.map.end)
		{
			is_static_ant = 1;
			ptr2 = e->anim.transitions;
			while (ptr2 != NULL)
			{
				tr = (t_transition *)(ptr2->content);
				if (tr->to == room)
				{
					is_static_ant = 0;
					break;
				}
				ptr2 = ptr2->next;
			}
			if (is_static_ant)
				ft_lstadd(&(e->anim.static_ants_rooms), ft_lstnew_ptr(room, sizeof(t_room)));
		}
		ptr = ptr->next;
	}
}

t_transition *ft_new_transition(t_env *e, t_room *from, t_room *to, int ant_num)
{
	t_transition *res;

	if (!from || !to)
	{
		ft_printf("transition error, look at the subject output example.\n");
		exit(1);
	}
	res = (t_transition *)(malloc(sizeof(t_transition)));
	from->ant_count--;
	if (from == e->lem.map.start)
	{
		if (from->ant_count == 0)
			from->ant_number = 0;
		else
			from->ant_number++;
	}
	else
		from->ant_number = 0;
	if (to == e->lem.map.end)
		e->lem.map.toward_end++;
	to->ant_count++;
	to->ant_number = ant_num;
	res->from = from;
	res->to = to;
	res->ant_num = ant_num;
	return (res);
}

void	ft_add_transition(t_env *e, int ant_numero, char *room_name)
{
	t_room *from;
	t_room *to;
	t_list *ptr;
	t_room *room;
	t_transition *transition;

	ptr = e->lem.map.rooms;
	from = NULL;
	to = NULL;
	while (ptr != NULL && (from == NULL || to == NULL))
	{
		room = (t_room *)(ptr->content);
		if (room->ant_number == ant_numero)
			from = room;
		else if (!ft_strcmp(room->name, room_name))
			to = room;
		ptr = ptr->next;
	}
	transition = ft_new_transition(e, from, to, ant_numero);
	ft_lstpushback(&(e->anim.transitions), ft_lstnew_ptr(transition, sizeof(t_transition)));
}

void	ft_add_transitions(t_env *e, char *str)
{
	char **split;
	int i;
	char **ant_split;

	i = 0;
	split = ft_strsplit(str,' ');
	while (split[i])
	{
		ant_split = ft_strsplit(split[i], '-');
		ft_add_transition(e, ft_atoi(&(ant_split[0][1])), ant_split[1]);
		i++;
	}
}

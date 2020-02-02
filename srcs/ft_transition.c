/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:07:53 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 15:52:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

t_transition	*ft_new_transition(t_room *from, t_room *to)
{
	t_transition *res;

	if (!(res = (t_transition *)(malloc(sizeof(t_transition)))))
		return (NULL);
	res->from = from;
	res->to = to;
	return (res);
}

t_transition	*ft_get_transition_to(t_list *transitions, t_room *to)
{
	t_list			*ptr;
	t_transition	*tr;

	ptr = transitions;
	while (ptr != NULL)
	{
		tr = (t_transition *)(ptr->content);
		if (tr->to == to)
			return (tr);
		ptr = ptr->next;
	}
	return (NULL);
}

void			ft_apply_transition(t_env *e, t_room *from, t_room *to)
{
	if (to == e->lem.map.end)
		e->toward_end++;
	from->ant_count--;
	to->ant_count++;
}

int				ft_already_in_transitions(t_list *transitions,
					t_room *from, t_room *to)
{
	t_list			*ptr;
	t_transition	*transition;

	ptr = transitions;
	while (ptr != NULL)
	{
		transition = (t_transition *)(ptr->content);
		if (from == transition->from && to == transition->to)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int				ft_process_ant_transition(t_vant *vant, t_room *to, t_env *e)
{
	t_transition	*transition;

	transition = ft_new_transition(e->lem.map.start, to);
	ft_apply_transition(e, e->lem.map.start, to);
	vant->room = to;
	if (ft_add_to_list_ptr(&(e->anim.transitions),
				transition, sizeof(t_transition)))
	{
		free(transition);
		free(vant);
		return (1);
	}
	return (0);
}

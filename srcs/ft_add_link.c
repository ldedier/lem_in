/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:15:42 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 13:15:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		ft_process_add_link(t_room *r1, t_room *r2, char *str, t_lem *lem)
{
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
	{
		ft_verbose(lem, str, "invalid room name");
		return (-1);
	}
}

int		ft_add_link(char *str, t_lem *lem)
{
	t_room	*r1;
	t_room	*r2;
	char	**split;

	split = ft_strsplit(str, '-');
	if (ft_splitlen(split) == 2)
	{
		r1 = ft_get_room((lem->map.rooms), split[0]);
		r2 = ft_get_room((lem->map.rooms), split[1]);
	}
	else
	{
		ft_free_split(split);
		ft_verbose(lem, str, "invalid link");
		return (-1);
	}
	ft_free_split(split);
	return (ft_process_add_link(r1, r2, str, lem));
}

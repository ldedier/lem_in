/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:35:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/12 17:36:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_common_checks(char *str)
{
	if (!ft_strncmp(str, "#", 1) &&
			ft_strncmp(str, "##end", 5) &&
				(ft_strncmp(str, "##start", 7)))
		return (1);
	else
		return (0);
}

int		ft_special_rooms_check(char *str, t_lem *lem)
{
	if (!ft_strncmp(str, "##start", 7)) 
	{
		if (++lem->parser.nb_start > 1)
			return (-1);
		else
		{
			lem->parser.phase = e_phase_start;
			return (1);
		}
	}
	else if (!ft_strncmp(str, "##end", 5))
	{
		if (++lem->parser.nb_end > 1)
			return (-1);
		else
		{
			lem->parser.phase = e_phase_end;
			return (1);
		}
	}
	return (0);
}

int		ft_describe_link(char *str)
{
	int i;
	int nb_minus;

	i = 0;
	nb_minus = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (0);
		if (str[i] == '-')
			nb_minus++;
		i++;
	}
	return (nb_minus == 1);
}

int		ft_links_transition_check(char *str, t_lem *lem)
{
	if (ft_describe_link(str))
	{
		lem->parser.phase = e_phase_links;
		return (ft_phase_links(str, lem));
	}
	return (0);
}

int		ft_isdigit_string(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (i);
}

int		ft_phase_nb_ants(char *str, t_lem *lem)
{
	int ret;
	if ((ret = ft_common_checks(str)))
		return (ret);
	if (!ft_isdigit_string(str))
		return (-1);
	else
	{
		lem->map.total_ants = ft_atoi(str);
		lem->parser.phase = e_phase_rooms;
	}
	return (0);
}

int		ft_share_same_infos(t_list *rooms, char **infos)
{
	while (rooms != NULL)
	{
		if ((((((t_room *)(rooms->content))->x == ft_atoi(infos[1])))
			&& ((t_room *)(rooms->content))->y == ft_atoi(infos[2]))
				|| (!(ft_strcmp(((t_room *)(rooms->content))->name, infos[0]))))
			return (1);
		rooms = rooms->next;
	}
	return (0);
}

int		ft_is_valid_room(char **split, t_lem *lem)
{
	if (ft_splitlen(split) != 3)
	{
		ft_printf("%d\n", ft_splitlen(split));
		return (0);
	}
	else
	{
		if(!ft_isdigit_string(split[1]) || 
			!ft_isdigit_string(split[2]))
			return (0);
		else if (ft_share_same_infos(lem->map.rooms, split))
			return (0);
	}

	return (1);
}

void	ft_init_ant_room(t_room *room)
{
	room->ant_number = 0;
	room->ant_count = 0;
}

int		ft_add_room(char *str, t_lem *lem, int role)
{
	char **split;
	t_room *room;
	split = ft_strsplit(str, ' ');
	if (ft_is_valid_room(split, lem))
	{
		room = malloc(sizeof(t_room));
		room->name = ft_strdup(split[0]);
		room->x = ft_atoi(split[1]);
		room->y = ft_atoi(split[2]);
		ft_init_ant_room(room);
		ft_lstadd(&(lem->map.rooms),ft_lstnew_ptr(room, sizeof(t_room)));
		if (role == START)
		{
			room->ant_number = 1;
			room->ant_count = lem->map.total_ants;
			lem->map.start = room;
		}
		else if (role == END)
			lem->map.end = room;
		lem->parser.phase = e_phase_rooms;
		return(0);
	}
	else
		return (-1);
}

t_room	*ft_get_room(t_list *rooms, char *str)
{
	while (rooms != NULL)
	{
		if (!ft_strcmp(((t_room *)(rooms->content))->name, str))
			return ((t_room *)(rooms->content));
		rooms = rooms->next;
	}
	return NULL;
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
	if (r1 && r2 && ft_not_linked_yet(r1, r2))
	{
		ft_lstadd(&(r1->neighbours),ft_lstnew_ptr(r2, sizeof(t_room)));
		ft_lstadd(&(r2->neighbours),ft_lstnew_ptr(r1, sizeof(t_room)));
		return (1);
	}
	else
		return (-1);
}

int		ft_phase_rooms(char *str, t_lem *lem)
{
	int ret;

	if ((ret = ft_common_checks(str)))
		return (ret);
	if ((ret = ft_special_rooms_check(str, lem)))
		return (ret);
	if ((ret = ft_links_transition_check(str, lem)))
		return (ret);
	return (ft_add_room(str, lem, NONE));
}

int		ft_phase_start(char *str, t_lem *lem)
{
	int ret;

	if ((ret = ft_common_checks(str)))
		return (ret);
	if ((ret = ft_special_rooms_check(str, lem)))
		return (ret);
	return (ft_add_room(str, lem, START));
}
int		ft_phase_end(char *str, t_lem *lem)
{
	int ret;

	if ((ret = ft_common_checks(str)))
		return (ret);
	if ((ret = ft_special_rooms_check(str, lem)))
		return (ret);
	return (ft_add_room(str, lem, END));
}

int		ft_phase_links(char *str, t_lem *lem)
{
	int ret;

	if ((ret = ft_common_checks(str)))
		return (ret);
	return (ft_add_link(str, lem));
}

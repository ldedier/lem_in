/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 21:44:43 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/23 15:34:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_isdigit_string(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{

		if (!(ft_isdigit(str[i])) && !(i == 0 && str[i] == '-'))
			return (0);
		i++;
	}
	return (i);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 21:44:43 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/19 17:41:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_is_atoiable(char *s)
{
	long	res;
	int		start;
	int		i;

	res = 0;
	start = 0;
	while (ft_isseparator(s[start]))
		start++;
	i = start;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
	{
		if ((s[start] != '-' && (res * 10 + s[i] - '0' <= 2147483647))
				|| (s[start] == '-' && (res * 10 + s[i] - '0' <= 2147483648)))
			res = res * 10 + s[i] - '0';
		else
			return (0);
		i++;
	}
	return (1);
}

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
		{
			return (1);
		}
		rooms = rooms->next;
	}
	return (0);
}

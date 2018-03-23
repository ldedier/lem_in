/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 00:35:45 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/22 21:08:15 by ldedier          ###   ########.fr       */
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
		if (lem->parser.nb_end != 1 || lem->parser.nb_start != 1)
			return (-1);
		lem->parser.phase = e_phase_links;
		return (ft_phase_links(str, lem));
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
		if (!ft_isdigit_string(split[1]) ||
			!ft_isdigit_string(split[2]))
			return (0);
		else if (ft_share_same_infos(lem->map.rooms, split))
			return (0);
	}
	return (1);
}

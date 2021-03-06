/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_phases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:45:22 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 19:00:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_phase_nb_ants(char *str, t_lem *lem)
{
	int ret;

	if ((ret = ft_common_checks(str)))
		return (ret);
	if (!ft_isdigit_string(str) || !ft_is_atoiable(str) || ft_atoi(str) <= 0)
		return (ft_verbose(lem, str,
			"does not describe a valid number of ants"));
	else
	{
		lem->map.total_ants = ft_atoi(str);
		lem->parser.phase = e_phase_rooms;
	}
	return (1);
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
	ret = ft_add_link(str, lem);
	return (ret);
}

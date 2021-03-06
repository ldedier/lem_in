/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_lem_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:40:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:56:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_fill_metadata(t_lem *lem)
{
	if (ft_fill_mps(lem))
		return (1);
	if (ft_fill_matching_smps(lem))
		return (1);
	return (0);
}

int		ft_process_lem_in(t_lem *lem)
{
	t_path *chosen;

	if (ft_fill_paths(lem))
		return (1);
	if (lem->paths.min_length)
	{
		if (ft_fill_metadata(lem))
			return (1);
	}
	chosen = ft_chosen_path(lem);
	if (ft_print_solution(lem, chosen))
		return (1);
	return (0);
}

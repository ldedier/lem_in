/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smp2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:25:02 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:26:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_is_compatible_smp_to_single_path(t_path *smp, t_path *single)
{
	if (ft_lstlength(smp->mps) <= ft_lstlength(single->mps))
		return (0);
	return (1);
}

int		ft_process_fill_matching_smps(t_list *current, t_list *to_compare)
{
	if (current != to_compare &&
			((t_path *)(to_compare->content))->mps != NULL &&
			ft_is_compatible_smp_to_single_path(to_compare->content,
				current->content))
	{
		if (ft_update_matching_smps((t_path *)current->content,
					(t_path *)(to_compare->content)))
			return (1);
	}
	return (0);
}

int		ft_fill_matching_smps(t_lem *lem)
{
	t_list	*current;
	t_list	*to_compare;

	current = lem->paths.paths_list;
	while (current != NULL)
	{
		if (((t_path *)current->content)->length == lem->paths.min_length)
		{
			to_compare = lem->paths.paths_list;
			while (to_compare != NULL)
			{
				if (ft_process_fill_matching_smps(current, to_compare))
					return (1);
				to_compare = to_compare->next;
			}
		}
		current = current->next;
	}
	return (0);
}

int		ft_nb_mps_smp(t_path *path)
{
	if (path->semi_mp)
		return (ft_lstlength(path->semi_mp->path->mps));
	return (0);
}

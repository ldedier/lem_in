/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:22:32 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:22:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_add_to_mps(t_list **mps, t_path *path)
{
	if (!ft_overlaps_path_list(mps, path))
	{
		if (ft_add_to_list_ptr(mps, path, sizeof(t_path)))
			return (1);
	}
	return (0);
}

int		ft_process_add_to_mps(t_path *path1, t_path *path2)
{
	if (ft_add_to_mps(&(path1->mps), path2))
		return (1);
	if (ft_add_to_mps(&(path2->mps), path1))
		return (1);
	return (0);
}

int		ft_update_mps(t_path *path1, t_path *path2)
{
	t_list	*current;
	t_list	*current2;
	int		i;
	int		j;

	current = path1->rooms;
	i = 0;
	while (current != NULL)
	{
		j = 0;
		current2 = path2->rooms;
		while (current2 != NULL)
		{
			if (current->content == current2->content)
				return (0);
			current2 = current2->next;
			j++;
		}
		current = current->next;
		i++;
	}
	if (ft_process_add_to_mps(path1, path2))
		return (1);
	return (0);
}

int		ft_fill_mps(t_lem *lem)
{
	t_list *current;
	t_list *to_compare;

	current = lem->paths.paths_list;
	while (current != NULL)
	{
		to_compare = current->next;
		while (to_compare != NULL)
		{
			ft_update_mps((t_path *)current->content,
					(t_path *)(to_compare->content));
			to_compare = to_compare->next;
		}
		current = current->next;
	}
	return (0);
}

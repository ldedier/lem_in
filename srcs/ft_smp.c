/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:19:07 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:57:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_semi_mp	*ft_new_semi_mp(size_t order, t_path *path)
{
	t_semi_mp *res;

	if (!(res = (t_semi_mp *)malloc(sizeof(t_semi_mp))))
		return (NULL);
	res->order = order;
	res->path = path;
	return (res);
}

int			ft_populate_smp(t_semi_mp **smp, size_t order, t_path *path)
{
	if (!(*smp))
	{
		if (!(*smp = ft_new_semi_mp(order, path)))
			return (1);
	}
	else
	{
		(*smp)->order = order;
		(*smp)->path = path;
	}
	return (0);
}

int			ft_is_better_smp(t_path *current, t_path *to_compare)
{
	return (ft_lstlength(current->mps) > ft_lstlength(to_compare->mps));
}

int			ft_process_match_smp(t_path *path1, t_path *path2, int i, int j)
{
	if (!path1->semi_mp ||
			ft_is_better_smp(path2, path1->semi_mp->path))
	{
		if (ft_populate_smp(&(path1->semi_mp), j - i, path2))
			return (1);
	}
	return (0);
}

int			ft_update_matching_smps(t_path *path1, t_path *path2)
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
			{
				if (j > i)
					return (ft_process_match_smp(path1, path2, i, j));
			}
			current2 = current2->next;
			j++;
		}
		current = current->next;
		i++;
	}
	return (0);
}

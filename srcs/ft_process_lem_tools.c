/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_lem_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:56:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:56:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_is_better_than(t_path *path, t_path *to_compare)
{
	return (ft_lstlength(path->mps) > ft_lstlength(to_compare->mps)
			|| ft_nb_mps_smp(path) > ft_nb_mps_smp(to_compare));
}

t_path	*ft_chosen_path(t_lem *lem)
{
	t_list	*paths;
	t_path	*path;
	t_path	*chosen;
	int		first;

	paths = lem->paths.paths_list;
	first = 1;
	chosen = NULL;
	while (paths != NULL)
	{
		path = (t_path *)(paths->content);
		if (first == 1 || (path->length == lem->paths.min_length
				&& ft_is_better_than(path, chosen)))
		{
			chosen = path;
			first = 0;
		}
		paths = paths->next;
	}
	return (chosen);
}

t_ant	*ft_new_ant(t_list *rooms)
{
	static int	i = 1;
	t_ant		*ant;

	if (!(ant = malloc(sizeof(t_ant))))
		return (NULL);
	ant->rooms = rooms;
	ant->id = i++;
	return (ant);
}

void	ft_list_sort(t_list **begin_list)
{
	t_list	*list_ptr;
	int		had_changes;
	void	*tmp;

	if (*begin_list == NULL)
		return ;
	had_changes = 1;
	while (had_changes == 1)
	{
		had_changes = 0;
		list_ptr = *begin_list;
		while (list_ptr->next != NULL)
		{
			if ((((t_path *)(list_ptr->content))->length >
					((t_path *)(list_ptr->next->content))->length))
			{
				tmp = list_ptr->content;
				list_ptr->content = list_ptr->next->content;
				list_ptr->next->content = tmp;
				had_changes = 1;
			}
			list_ptr = list_ptr->next;
		}
	}
}

int		ft_populate_platform(t_deploy_platform *p, t_path *chosen)
{
	t_list	*ptr;
	t_path	*path;
	int		min;
	int		val;

	if (ft_copy_list_ptr_rev(chosen->mps, &(p->paths)))
		return (1);
	if (ft_add_to_list_ptr(&(p->paths), chosen, sizeof(t_path)))
	{
		ft_lstdel_ptr(&(p->paths));
		return (1);
	}
	ft_list_sort(&(p->paths));
	min = chosen->length;
	ptr = p->paths;
	while (ptr != NULL)
	{
		path = (t_path *)(ptr->content);
		if (min > (val = path->length))
			min = val;
		ptr = ptr->next;
	}
	p->min_length = min;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_lem_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:40:06 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/17 15:56:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_add_path_from_rooms(t_list **paths, t_list *rooms, int length) //to protect
{
	t_list	*rooms_cpy;
	t_path	*path;
   
	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (1);
	if (rooms)
	{
		if (!(rooms_cpy = ft_copy_list_ptr_rev(rooms)))
			return (1);
	}
	else
		rooms_cpy = NULL;
	path->length = length;
	path->rooms = rooms_cpy;
	path->semi_mp = NULL;
	path->mps = NULL;
	if (ft_add_to_list_ptr(paths, path, sizeof(t_path)))
		return (1);
	return (0);
}

int		ft_process_fill(t_room *room, t_lem *lem, t_list **path, int *max_paths)
{
	t_list	*current;
	int		length;

	if (!room->parsed && *max_paths != 0)
	{
		room->parsed = 1;
		if (room != lem->map.start && room != lem->map.end)
		{
			if (ft_add_to_list_ptr(path, room, sizeof(t_room)))
				return (1);
		}
		if (room != lem->map.end)
		{
			current = room->neighbours;
			while (current != NULL)
			{
				if (ft_process_fill((t_room *)(current->content), lem, path, max_paths))
					return (1);
				current = current->next;
			}
			if (room != lem->map.start)
				ft_lstpop_ptr(path);
		}
		else
		{
			length = ft_lstlength(*path);
			if ((length < lem->paths.min_length) ||
					(lem->paths.min_length == -1))
				lem->paths.min_length = length;
			if (ft_add_path_from_rooms(&(lem->paths.paths_list), *path, length))
				return (1);
			if (*path == NULL)
				*max_paths = 0;
			else
				*max_paths -= 1;
		}
		room->parsed = 0;
	}
	return (0);
}

int		ft_fill_paths(t_lem *lem)
{
	t_list	*path;
	int		max_paths;

	max_paths = 10000000;
	path = NULL;
	if (ft_process_fill(lem->map.start, lem, &path, &max_paths))
		return (1);
	return (0);
}

t_semi_mp	*ft_new_semi_mp(size_t order, t_path *path)
{
	t_semi_mp *res;

	if (!(res = (t_semi_mp *)malloc(sizeof(t_semi_mp))))
		return (NULL);
	res->order = order;
	res->path = path;
	return (res);
}

int		ft_populate_smp(t_semi_mp **smp, size_t order, t_path *path)
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

int		ft_is_better_smp(t_path *current, t_path *to_compare)
{
	return (ft_lstlength(current->mps) > ft_lstlength(to_compare->mps));
}

int		ft_update_matching_smps(t_path *path1, t_path *path2)
{
	t_list *current;
	t_list *current2;

	int i;
	int j;
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
				{
					if (!path1->semi_mp ||
							ft_is_better_smp(path2, path1->semi_mp->path))
					{
						if (ft_populate_smp(&(path1->semi_mp), j - i, path2))
							return (1);
					}
					return (0);
				}
			}
			current2 = current2->next;
			j++;
		}
		current = current->next;
		i++;
	}
	return (0);
}

int		ft_share_rooms(t_path *path1, t_path *path2)
{
	t_list	*rooms1;
	t_list	*rooms2;

	rooms1 = path1->rooms;
	while (rooms1 != NULL)
	{
		rooms2 = path2->rooms;
		while (rooms2 != NULL)
		{
			if (rooms1->content == rooms2->content)
				return (1);
			rooms2 = rooms2->next;
		}
		rooms1 = rooms1->next;
	}
	return (0);
}

int		ft_overlaps_path_list(t_list **path_list, t_path* path)
{
	t_list	*ptr;
	t_path	*current;
	t_list	*overlapping;
	t_list	*prev;

	ptr = *path_list;
	overlapping = NULL;
	prev = NULL;
	while (ptr != NULL)
	{
		current = (t_path *)(ptr->content);
		if (ft_share_rooms(current, path))
		{
			if (overlapping || current->length <= path->length)
				return (1);
			else
				overlapping = ptr;
		}
		if (!overlapping)
			prev = ptr;
		ptr = ptr->next;
	}
	if (overlapping)
	{
		if (prev == NULL)
			*path_list = (*path_list)->next;
		else
			prev->next = prev->next->next;
		free(overlapping);
	}
	return (0);
}

int		ft_add_to_mps(t_list **mps, t_path *path)
{
	if (!ft_overlaps_path_list(mps, path))
	{
		if (ft_add_to_list_ptr(mps, path, sizeof(t_path)))
			return (1);
	}
	return (0);
}

int		ft_update_mps(t_path *path1, t_path *path2)
{
	t_list *current;
	t_list *current2;

	int i;
	int j;
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
	if (ft_add_to_mps(&(path1->mps), path2))
		return (1);
	if (ft_add_to_mps(&(path2->mps), path1))
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

int		ft_is_compatible_smp_to_single_path(t_path *smp, t_path *single) //CHECK
{
	if (ft_lstlength(smp->mps) <= ft_lstlength(single->mps)) //todo
		return (0);
	return (1);
}

int		ft_fill_matching_smps(t_lem *lem)
{
	t_list *current;
	t_list *to_compare;
	current = lem->paths.paths_list;

	while (current != NULL)
	{
		if (((t_path *)current->content)->length == lem->paths.min_length)
		{
			to_compare = lem->paths.paths_list;
			while (to_compare != NULL)
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
				to_compare = to_compare->next;
			}
		}
		current = current->next;
	}
	return (0);
}

int		ft_fill_metadata(t_lem *lem)
{
	if (ft_fill_mps(lem))
		return (1);
	if (ft_fill_matching_smps(lem))
		return (1);
	return (0);
}

int		ft_nb_mps_smp(t_path *path)
{
	if (path->semi_mp)
		return ft_lstlength(path->semi_mp->path->mps);
	return (0);
}

int		ft_is_better_than(t_path *path, t_path *to_compare)
{
	return (ft_lstlength(path->mps) > ft_lstlength(to_compare->mps)
			|| ft_nb_mps_smp(path) > ft_nb_mps_smp(to_compare));
}

t_path	*ft_chosen_path(t_lem *lem)
{
	t_list *paths;
	t_path *path;
	t_path *chosen;
	int first;

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

int		ft_print_all_in_one(t_lem *lem)
{
	int i;

	i = 1;
	while (i < lem->map.total_ants)
	{
		ft_printf("L%d-%s ", i, lem->map.end->name);
		i++;
	}
	if (lem->map.total_ants > 0)
		ft_printf("L%d-%s\n", i, lem->map.end->name);
	return (0);
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

int		ft_deploy_ant(t_deploy *deploy, t_list *rooms)
{
	t_ant *ant;

	if (!(ant = ft_new_ant(rooms)))
		return (1);
	if (ft_add_to_list_ptr_back(&(deploy->ants), ant, sizeof(t_ant)))
	{
		free(ant);
		return (1);
	}
	deploy->ants_released++;
	return (0);
}

int		ft_deploy_ants(t_deploy *deploy, t_lem *lem)
{
	int		total_ants;
	t_list	*ptr;
	t_path	*path;

	total_ants = lem->map.total_ants;
	ptr = deploy->p.paths;
	while (ptr != NULL && deploy->ants_released < lem->map.total_ants)
	{
		path = (t_path *)(ptr->content);
		if (path->length == deploy->p.min_length ||
				lem->map.total_ants - deploy->ants_released >= path->length)
			ft_deploy_ant(deploy, path->rooms);
		ptr = ptr->next;
	}
	return (0);
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
	int min;
	int val;

	if(chosen->mps)
	{
		if (!(p->paths = ft_copy_list_ptr_rev(chosen->mps)))
			return (1);
	}
	else
		p->paths = NULL;
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

void	ft_affich_progress_ant(int id, char *room_name, int first)
{
	if (first)
		ft_printf("L%d-%s", id, room_name);
	else
		ft_printf(" L%d-%s", id, room_name);
}

int		ft_progress_ant(t_ant *ant, t_lem *lem)
{
	if (ant->rooms)
	{
		ft_affich_progress_ant(ant->id, ((t_room *)(ant->rooms->content))->name,
				lem->first);
		lem->first = 0;
		ant->rooms = ant->rooms->next;
		return (0);
	}
	else
	{
		ft_affich_progress_ant(ant->id, lem->map.end->name, lem->first);
		lem->first = 0;
		return (1);
	}
}

void	ft_progress_ants(t_deploy *deploy, t_lem *lem)
{
	t_list *temp = deploy->ants;
	t_list  *prev;

	prev = NULL;	
	while (temp != NULL && ft_progress_ant((t_ant *)(temp->content), lem))
	{
		deploy->ants = temp->next;
		free(temp->content);
		free(temp);
		temp = deploy->ants;
		deploy->ants_end += 1;
	}
	if (temp != NULL)
	{
		prev = temp;
		temp = temp->next;
	}
	while (temp != NULL)
	{
		while (temp != NULL && !ft_progress_ant((t_ant *)(temp->content), lem))
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp != NULL)
		{
			prev->next = temp->next;
			free(temp->content);
			free(temp);
			deploy->ants_end += 1;
			temp = prev->next;
		}
	}
}

int		ft_deploy_ants_smp(t_path *chosen, t_deploy *deploy, t_lem *lem)
{
	if (deploy->ants_released < lem->map.total_ants)
		ft_deploy_ant(deploy, chosen->rooms);
	if (deploy->ants_released < lem->map.total_ants)
		ft_deploy_ant(deploy, chosen->semi_mp->path->rooms);
	return (0);
}

int		ft_process_print_no_smp(t_lem *lem, t_path *chosen, t_deploy *deploy)
{
	if (ft_populate_platform(&(deploy->p), chosen))
		return (1);
	while (deploy->ants_end < lem->map.total_ants)
	{
		lem->first = 1;
		if (ft_deploy_ants(deploy, lem))
			return (1);
		ft_progress_ants(deploy, lem);
		ft_printf("\n");
	}
	ft_lstdel_value(&(deploy->ants));
	return (0);
}

int		ft_process_print_smp(t_lem *lem, t_path *chosen, t_deploy *deploy)
{
	size_t i;

	i = 0;
	while (deploy->ants_end < lem->map.total_ants && i < chosen->semi_mp->order)
	{
		lem->first = 1;
		if (ft_deploy_ants_smp(chosen, deploy, lem))
			return (1);
		ft_progress_ants(deploy, lem);
		ft_printf("\n");
		i++;
	}
	return ft_process_print_no_smp(lem, chosen->semi_mp->path, deploy);
}

void	ft_init_deploy(t_deploy *deploy)
{
	deploy->ants_released = 0;
	deploy->ants_end = 0;
	deploy->ants = NULL;
}

int		ft_process_print(t_lem *lem, t_path *chosen)
{
	t_deploy	deploy;

	ft_init_deploy(&deploy);
	if (!chosen->semi_mp)
		ft_process_print_no_smp(lem, chosen, &deploy);
	else
		ft_process_print_smp(lem, chosen, &deploy);
	ft_lstdel_ptr(&(deploy.p.paths));
	return (0);
}

int		ft_print_solution(t_lem *lem, t_path *chosen)
{
	if (!ft_lstlength(chosen->rooms))
		ft_print_all_in_one(lem);
	else
		ft_process_print(lem, chosen);
	return (0);
}

int     ft_process_lem_in(t_lem *lem)
{
	t_path *chosen;
	if (ft_fill_paths(lem))
		return (1);
	if (lem->paths.min_length)
	{
		if (ft_fill_metadata(lem))
			return (1);
	}
	chosen = ft_chosen_path(lem); //check has path !
	ft_print_solution(lem, chosen);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deploy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:33:56 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:53:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		ft_deploy_ants_smp(t_path *chosen, t_deploy *deploy, t_lem *lem)
{
	if (deploy->ants_released < lem->map.total_ants)
		ft_deploy_ant(deploy, chosen->rooms);
	if (deploy->ants_released < lem->map.total_ants)
		ft_deploy_ant(deploy, chosen->semi_mp->path->rooms);
	return (0);
}

void	ft_init_deploy(t_deploy *deploy)
{
	deploy->ants_released = 0;
	deploy->ants_end = 0;
	deploy->ants = NULL;
}

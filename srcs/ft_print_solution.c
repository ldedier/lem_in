/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_solution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:39:39 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:58:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		ft_process_print_no_smp(t_lem *lem, t_path *chosen, t_deploy *deploy)
{
	if (ft_populate_platform(&(deploy->p), chosen))
		return (1);
	while (deploy->ants_end < lem->map.total_ants)
	{
		lem->first = 1;
		if (ft_deploy_ants(deploy, lem))
		{
			ft_lstdel_value(&(deploy->ants));
			return (1);
		}
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
	return (ft_process_print_no_smp(lem, chosen->semi_mp->path, deploy));
}

int		ft_process_print(t_lem *lem, t_path *chosen)
{
	t_deploy	deploy;

	ft_init_deploy(&deploy);
	if (!chosen->semi_mp)
	{
		if (ft_process_print_no_smp(lem, chosen, &deploy))
		{
			ft_lstdel_ptr(&(deploy.p.paths));
			return (1);
		}
	}
	else
	{
		if (ft_process_print_smp(lem, chosen, &deploy))
		{
			ft_lstdel_ptr(&(deploy.p.paths));
			return (1);
		}
	}
	ft_lstdel_ptr(&(deploy.p.paths));
	return (0);
}

int		ft_print_solution(t_lem *lem, t_path *chosen)
{
	if (!ft_lstlength(chosen->rooms))
		return (ft_print_all_in_one(lem));
	else
		return (ft_process_print(lem, chosen));
}

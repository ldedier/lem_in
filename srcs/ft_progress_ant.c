/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_progress_ant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:30:41 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 16:31:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	ft_progress_all_at_head(t_list **temp, t_list **prev, t_lem *lem,
			t_deploy *deploy)
{
	while (*temp != NULL && ft_progress_ant((t_ant *)((*temp)->content), lem))
	{
		deploy->ants = (*temp)->next;
		free((*temp)->content);
		free(*temp);
		*temp = deploy->ants;
		deploy->ants_end += 1;
	}
	if (*temp != NULL)
	{
		*prev = *temp;
		*temp = (*temp)->next;
	}
}

void	ft_progress_all_at_body(t_list **temp, t_list **prev, t_lem *lem,
			t_deploy *deploy)
{
	while (*temp != NULL)
	{
		while (*temp != NULL &&
			!ft_progress_ant((t_ant *)((*temp)->content), lem))
		{
			*prev = *temp;
			*temp = (*temp)->next;
		}
		if (*temp != NULL)
		{
			(*prev)->next = (*temp)->next;
			free((*temp)->content);
			free(*temp);
			deploy->ants_end += 1;
			*temp = (*prev)->next;
		}
	}
}

/*
** make progress and delete all ants arrived at the end
*/

void	ft_progress_ants(t_deploy *deploy, t_lem *lem)
{
	t_list	*temp;
	t_list	*prev;

	temp = deploy->ants;
	prev = NULL;
	ft_progress_all_at_head(&temp, &prev, lem, deploy);
	ft_progress_all_at_body(&temp, &prev, lem, deploy);
}

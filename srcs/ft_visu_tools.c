/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/14 21:57:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

void	ft_affich_transitions(t_env *e)
{
	t_list *ptr;
	t_transition *tr;

	ptr = e->anim.transitions;
	while (ptr != NULL)
	{
		tr = (t_transition *)(ptr->content);
		ft_printf("from: %s\n", tr->from->name);
		ft_printf("to: %s\n", tr->to->name);
		ptr = ptr->next;
	}
}

int		ft_parse_visu(t_lem *lem)
{
	char	*str;
	int		ret;

	t_parse_func parse_arr[5];
	ft_init_parser(&(lem->parser));
	ft_init_parse_arr(parse_arr);
	while ((ret = get_next_line(0, &str)) > 0 && ft_strcmp(str, ""))
	{
		if (parse_arr[lem->parser.phase](str, lem) == -1)
			return (-1);
	}
	if (ft_check_post_parse(lem) == -1)
		return (-1);
	else
		return (0);
}

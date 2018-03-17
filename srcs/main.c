/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/16 19:06:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lem	lem;
	char	*to_print;

	lem.map.rooms = NULL;
	if ((to_print = ft_parse(&lem)) == NULL)
		ft_printf("ERROR\n");
	else
	{
		ft_printf("%s\n", to_print);
		if (ft_process_lem_in(&(lem.map)) == -1)
			ft_printf("ERROR\n");
	}
	//ft_affich_map(&(lem.map));
	return (0);
}

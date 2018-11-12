/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/12 13:35:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_init_lem(t_lem *lem, int argc, char **argv)
{
	lem->map.rooms = NULL;
	lem->paths.paths_list = NULL;
	lem->paths.multipaths_list = NULL;
	lem->verbosed = 0;
	lem->paths.min_length = -1;
	if (argc >= 2)
	{
		if (argc > 2 || ft_strcmp(argv[1], "-v"))
			ft_printf("usage!!");
		else
			lem->verbosed = 1;
	}
}

int		main(int argc, char **argv)
{
	t_lem	lem;
	char	*to_print;

	ft_init_lem(&lem, argc, argv);
	if ((to_print = ft_parse(&lem)) == NULL)
	{
		if (!lem.verbosed)
			ft_printf("ERROR\n");
	}
	else
	{
		ft_printf("%s\n", to_print);
		if (ft_process_lem_in(&lem) == -1 && !lem.verbosed)
			ft_printf("ERROR\n");
	}
	return (0);
}

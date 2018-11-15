/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/15 18:09:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void __attribute__((destructor)) end();

void	end(void)
{
	ft_printf("destructor loop\n");
	while(1);
}

void	ft_init_lem(t_lem *lem, int argc, char **argv)
{
	lem->map.rooms = NULL;
	lem->paths.paths_list = NULL;
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

void	ft_delete_paths(t_list **paths)
{
	t_list	*ptr;
	t_path	*path;

	ptr = *paths;
	
	while (ptr != NULL)
	{
		path = (t_path *)(ptr->content);
		ft_printf("AVANT DE DELETE\n\n\n");
	//	ft_affich_path(path, 1); //EXPLODE
	//	ft_lstdel_ptr(&(path->mps)); //EXPLODE
		ft_lstdel_ptr(&(path->rooms));
		ft_printf("DELETED MPS\n\n\n");
//		ft_affich_path(path, 1); //EXPLODE
		if (path->semi_mp)
			free(path->semi_mp);
		free(path);
		path = NULL;
		ptr = ptr->next;
	}
	ft_lstdel_ptr(paths);
}

void	ft_delete_rooms(t_list **rooms)
{
	t_list	*ptr;
	t_room	*room;

	ptr = *rooms;
	while (ptr != NULL)
	{
		room = (t_room *)(ptr->content);
		ft_lstdel_ptr(&(room->neighbours));
		ft_strdel(&(room->name));
		free(room);
		ptr = ptr->next;
	}
	ft_lstdel_ptr(rooms);
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
		ft_strdel(&to_print);
		if (ft_process_lem_in(&lem) == -1 && !lem.verbosed)
			ft_printf("ERROR\n");
		ft_delete_paths(&(lem.paths.paths_list));
		ft_delete_rooms(&(lem.map.rooms));
	}
	return (0);
}

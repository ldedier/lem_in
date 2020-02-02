/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 20:53:20 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_print_usage(void)
{
	ft_printf("./lem-in [optional: -v] < [map_name] | ./lem-in_visu\n");
}

int		ft_init_lem(t_lem *lem, int argc, char **argv)
{
	lem->map.rooms = NULL;
	lem->map.is_solvable = 0;
	lem->paths.paths_list = NULL;
	lem->verbosed = 0;
	lem->paths.min_length = -1;
	if (argc >= 2)
	{
		if (argc > 2 || ft_strcmp(argv[1], "-v"))
		{
			ft_print_usage();
			return (1);
		}
		else
			lem->verbosed = 1;
	}
	return (0);
}

void	ft_delete_paths(t_list **paths)
{
	t_list	*ptr;
	t_path	*path;

	ptr = *paths;
	while (ptr != NULL)
	{
		path = (t_path *)(ptr->content);
		ft_lstdel_ptr(&(path->mps));
		ft_lstdel_ptr(&(path->rooms));
		if (path->semi_mp)
			free(path->semi_mp);
		free(path);
		path = NULL;
		ptr = ptr->next;
	}
	ft_lstdel_ptr(paths);
}

int		main(int argc, char **argv)
{
	t_lem	lem;
	char	*to_print;

	if (ft_init_lem(&lem, argc, argv))
		return (1);
	if ((to_print = ft_parse(&lem)) == NULL)
		ft_printf("malloc error\n");
	else
	{
		if (ft_is_valid_post_parse(&lem) == 1)
		{
			ft_printf("%s\n", to_print);
			if (ft_process_lem_in(&lem) == 1)
				ft_printf("malloc error\n");
		}
		else
		{
			if (!lem.verbosed)
				ft_printf("ERROR\n");
		}
		ft_strdel(&to_print);
	}
	ft_delete_paths(&(lem.paths.paths_list));
	ft_delete_rooms(&(lem.map.rooms));
	return (0);
}

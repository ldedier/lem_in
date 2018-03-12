/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/12 17:36:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_init_parser(t_parser *parser)
{
	parser->nb_start = 0;
	parser->nb_end = 0;
	parser->phase = e_phase_nb_ants;
}

void	ft_init_parse_arr(t_parse_func parse_arr[5])
{
	parse_arr[0] = &ft_phase_nb_ants;
	parse_arr[1] = &ft_phase_rooms;
	parse_arr[2] = &ft_phase_start;
	parse_arr[3] = &ft_phase_end;
	parse_arr[4] = &ft_phase_links;
}

char	*ft_parse(t_lem *lem)
{
	char	*res;
	char	*str;
	int		ret;
	t_parse_func parse_arr[5];
	ft_init_parser(&(lem->parser));
	ft_init_parse_arr(parse_arr);
	res = ft_strnew(0);
	while ((ret = get_next_line(0, &str)) > 0)
	{
	//	ft_printf("phase: %d\n", lem->parser.phase);
	//	ft_printf("hoy: %s\n", str);
		if (parse_arr[lem->parser.phase](str, lem) == -1)
			return (NULL);
		if (!(res = ft_strjoin(res, str)))
			return (NULL);
		if (!(res = ft_strjoin(res, "\n")))
			return (NULL);
	}
	return (res);
}

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

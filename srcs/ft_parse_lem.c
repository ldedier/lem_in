/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/07/08 14:55:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_init_parser(t_parser *parser)
{
	parser->nb_start = 0;
	parser->nb_end = 0;
	parser->phase = e_phase_nb_ants;
	parser->nb_lines = 1;
}

void	ft_init_parse_arr(t_parse_func parse_arr[5])
{
	parse_arr[0] = &ft_phase_nb_ants;
	parse_arr[1] = &ft_phase_rooms;
	parse_arr[2] = &ft_phase_start;
	parse_arr[3] = &ft_phase_end;
	parse_arr[4] = &ft_phase_links;
}

int		ft_check_post_parse(t_lem *lem)
{
	if (lem->parser.nb_start == 0 || lem->parser.nb_end == 0)
		return (-1);	
	return (0);
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
		if (parse_arr[lem->parser.phase](str, lem) == -1)
			return (NULL);
		if (!(res = ft_strjoin(res, str)))
			return (NULL);
		if (!(res = ft_strjoin(res, "\n")))
			return (NULL);
		lem->parser.nb_lines++;
	}
	if (ft_check_post_parse(lem) == -1)
		return (NULL);
	else
		return (res);
}

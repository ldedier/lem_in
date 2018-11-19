/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/19 17:29:18 by ldedier          ###   ########.fr       */
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

int		ft_is_valid_post_parse(t_lem *lem)
{
	int ret;

	if (lem->parser.nb_start == 0)
	{
		ft_verbose_no_line(lem, "map has no start");
		return (0);
	}
	if (lem->parser.nb_end == 0)
	{
		ft_verbose_no_line(lem, "map has no end");
		return (0);
	}
	if ((ret = ft_is_solvable(&(lem->map))) == 0)
		ft_verbose_no_line(lem, "map start and end are not linked");
	else if(ret == -1)
		ft_printf("malloc error\n");
	return (ret);
}

char	*ft_free_turn_str(char *res, char **to_del)
{
	ft_strdel(to_del);
	return (res);
}

char	*ft_parse(t_lem *lem)
{
	char			*res;
	char			*str;
	int				ret;
	t_parse_func	parse_arr[5];

	ft_init_parser(&(lem->parser));
	ft_init_parse_arr(parse_arr);
	if (!(res = ft_strnew(0)))
		return (NULL);
	while ((ret = get_next_line(0, &str)) > 0)
	{
		if (parse_arr[lem->parser.phase](str, lem) == -1)
			return (ft_free_turn_str(res, &str));
		if (!(res = ft_strjoin_free(res, str)))
			return (ft_free_turn_str(NULL, &str));
		if (!(res = ft_strjoin_free(res, "\n")))
			return (ft_free_turn_str(NULL, &str));
		lem->parser.nb_lines++;
		ft_strdel(&str);
	}
	ft_strdel(&str);
	return (res);
}

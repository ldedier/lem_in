/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 22:27:14 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/18 17:05:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_lem_in.h"

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
		{
			ft_strdel(&(str));
			return (-1);
		}
		ft_strdel(&(str));
	}
	ft_strdel(&(str));
	if (!ft_is_valid_post_parse(lem))
		return (-1);
	else
		return (0);
}

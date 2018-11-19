/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 22:51:23 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/19 17:56:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_verbose(t_lem *lem, char *line_parsed, char *str)
{
	if (lem->verbosed)
	{
		ft_printf(RED"line %d:%s %s\n\t%s\n", lem->parser.nb_lines, EOC, line_parsed, str);
	}
	return (-1);
}

int			ft_verbose_no_line(t_lem *lem, char *str)
{
	if (lem->verbosed)
	{
		ft_printf(RED"error: %s%s\n", EOC, str);
	}
	return (-1);
}

void		ft_file_error(char *filename)
{
	ft_printf("file \"%s\"could not be loaded\n", filename);
}

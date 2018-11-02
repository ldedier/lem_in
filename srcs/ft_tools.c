/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 22:51:23 by ldedier           #+#    #+#             */
/*   Updated: 2018/07/08 15:08:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_error(char *error)
{
	ft_printf("%s", error);
	exit(1);
}

int			ft_verbose(t_lem *lem, char *line_parsed, char *str)
{
	if (lem->verbosed)
	{
		ft_printf(RED"line %d:%s %s\n\t%s\n", lem->parser.nb_lines, EOC, line_parsed, str);
	}
	return (-1);
}

void		ft_file_error(char *filename)
{
	ft_printf("file \"%s\"could not be loaded\n", filename);
	exit(1);
}

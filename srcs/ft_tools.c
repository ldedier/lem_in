/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 22:51:23 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/12 22:56:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_error(char *error)
{
	ft_printf("%s", error);
	exit(1);
}

void		ft_file_error(char *filename)
{
	ft_printf("file \"%s\"could not be loaded\n", filename);
	exit(1);
}

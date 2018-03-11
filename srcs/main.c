/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 12:55:17 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/11 15:57:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_parse(void)
{
	char	*str;
	int		ret;

	while ((ret = get_next_line(0, &str)) > 0)
	{
		ft_printf("%s\n", str);
	}
	return (0);
}

int		main(void)
{
	if (ft_parse() == -1)
		ft_printf("ERROR\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 18:54:49 by ldedier           #+#    #+#             */
/*   Updated: 2018/02/06 21:15:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_get_char_from_index(int index, int maj)
{
	if (index <= 9)
		return (index + '0');
	else
	{
		if (maj)
			return (index + 'A' - 10);
		else
			return (index + 'a' - 10);
	}
}

void		ft_puthex_max(uintmax_t nb, int maj)
{
	if ((nb / 16) == 0)
		ft_putchar_buff(ft_get_char_from_index(nb % 16, maj));
	else
	{
		ft_puthex_max((uintmax_t)nb / (uintmax_t)16, maj);
		ft_putchar_buff(ft_get_char_from_index(nb % 16, maj));
	}
}

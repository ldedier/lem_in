/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:02:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/12 02:35:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H

# include "../libft/srcs/libft.h"

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				is_special;
	int				nb_ants;
	t_list			*neighbours;
}					t_room;

typedef struct		s_map
{
	t_room			*start;
	t_room			*end;
	t_list			*rooms;
	int				total_ants;
}					t_map;


typedef enum		e_phase
{
	e_phase_nb_ants,
	e_phase_rooms,
	e_phase_start,
	e_phase_end,
	e_phase_links
}					t_phase;

typedef struct		s_parser
{
	t_phase			phase;
	int				nb_start;
	int				nb_end;
}					t_parser;

typedef struct		s_lem
{
	t_map			map;
	t_parser		parser;
}					t_lem;

typedef int         (*t_parse_func)(char *, t_lem *);

int					ft_phase_nb_ants(char *str, t_lem *lem);
int					ft_phase_rooms(char *str, t_lem *lem);
int					ft_phase_start(char *str, t_lem *lem);
int					ft_phase_end(char *str, t_lem *lem);
int					ft_phase_links(char *str, t_lem *lem);

#endif

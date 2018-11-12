/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:02:08 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/12 13:37:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H
# define NONE 0
# define START 1
# define END 2
# include "libft.h"
# include <math.h>

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				corr_x;
	int				corr_y;
	int				corr_x_init;
	int				corr_y_init;
	int				ant_number;
	int				ant_count;
	t_list			*neighbours;
	int				parsed;
}					t_room;

typedef struct		s_map
{
	t_room			*start;
	t_room			*end;
	t_list			*rooms;
	int				total_ants;
	int				toward_end;
}					t_map;


typedef enum		e_phase
{
	e_phase_nb_ants,
	e_phase_rooms,
	e_phase_start,
	e_phase_end,
	e_phase_links
}					t_phase;

typedef struct		s_multi_path
{
	t_list			*paths;
	int				path_count;
}					t_multi_path;

typedef struct		s_path
{
	int				length;
	t_list			*rooms; //list of rooms
	t_list			*semi_mps; // list of semi_mp
	t_list			*mps; //list of paths
}					t_path;

typedef struct		s_semi_mp
{
	size_t			order;
	t_path			*path; // path
}					t_semi_mp;

typedef struct		s_paths
{
	int				min_length;
	t_list			*paths_list; // list of t_path
	t_list			*multipaths_list;
}					t_paths;

typedef struct		s_parser
{
	t_phase			phase;
	int				nb_start;
	int				nb_end;
	int				nb_lines;
}					t_parser;

typedef struct		s_lem
{
	t_paths			paths;
	t_map			map;
	t_parser		parser;
	int				turn;
	int				verbosed;
}					t_lem;

typedef int         (*t_parse_func)(char *, t_lem *);

int					ft_phase_nb_ants(char *str, t_lem *lem);
int					ft_phase_rooms(char *str, t_lem *lem);
int					ft_phase_start(char *str, t_lem *lem);
int					ft_phase_end(char *str, t_lem *lem);
int					ft_phase_links(char *str, t_lem *lem);
void				ft_affich_map(t_map *map);
void				ft_affich_paths(t_list *paths, int rec);
void				ft_affich_path(t_path *path, int rec);
void				ft_affich_list_of_list(t_list *list);
void				ft_affich_map(t_map *map);
void				ft_affich_room(t_room *room);
void				ft_affich_room_lite(t_room *room);
void				ft_affich_queue(t_list *queue);
void				ft_affich_room_list(t_list *room_list);
int					ft_process_lem_in(t_lem *lem);
char				*ft_parse(t_lem *lem);
int					ft_common_checks(char *str);
int					ft_is_valid_room(char **split, t_lem *lem);
int					ft_isdigit_string(char *str);
int					ft_share_same_infos(t_list *rooms, char **split);
int					ft_special_rooms_check(char *str, t_lem *lem);
int					ft_links_transition_check(char *str, t_lem *lem);
int					ft_add_room(char *str, t_lem *lem, int indic);
int					ft_add_link(char *str, t_lem *lem);
void				ft_init_parser(t_parser *parser);
void				ft_init_parse_arr(t_parse_func arr[5]);
void				ft_error(char *error);
void				ft_file_error(char *filename);
int					ft_check_post_parse(t_lem *lem);
int					ft_verbose(t_lem *lem, char *line, char *str);
#endif

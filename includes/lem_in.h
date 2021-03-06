/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:07:12 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 18:51:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H
# include "libft.h"
# include <math.h>
# define NONE			0
# define START			1
# define END			2

typedef struct s_path	t_path;

typedef struct			s_ant
{
	int					id;
	t_list				*rooms;
}						t_ant;

typedef struct			s_room
{
	t_list				*neighbours;
	char				*name;
	int					x;
	int					y;
	int					corr_x;
	int					corr_y;
	int					corr_x_init;
	int					corr_y_init;
	int					ant_count;
	int					parsed;
	int					dist;
}						t_room;

typedef struct			s_map
{
	t_room				*start;
	t_room				*end;
	t_list				*rooms;
	int					total_ants;
	int					toward_end;
	int					is_solvable;
}						t_map;

typedef enum			e_phase
{
	e_phase_nb_ants,
	e_phase_rooms,
	e_phase_start,
	e_phase_end,
	e_phase_links
}						t_phase;

typedef struct			s_semi_mp
{
	size_t				order;
	t_path				*path;
}						t_semi_mp;

struct					s_path
{
	int					length;
	t_list				*rooms;
	t_list				*mps;
	t_semi_mp			*semi_mp;
};

typedef struct			s_paths
{
	int					max_paths;
	int					min_length;
	t_list				*paths_list;
}						t_paths;

typedef struct			s_parser
{
	t_phase				phase;
	int					nb_start;
	int					nb_end;
	int					nb_lines;
}						t_parser;

typedef struct			s_deploy_platform
{
	t_list				*paths;
	int					min_length;
}						t_deploy_platform;

typedef struct			s_deploy
{
	int					ants_released;
	int					ants_end;
	t_list				*ants;
	t_deploy_platform	p;
}						t_deploy;

typedef struct			s_lem
{
	t_paths				paths;
	t_map				map;
	t_parser			parser;
	int					turn;
	int					first;
	int					verbosed;
}						t_lem;

typedef int				(*t_parse_func)(char *, t_lem *);

int						ft_phase_nb_ants(char *str, t_lem *lem);
int						ft_phase_rooms(char *str, t_lem *lem);
int						ft_phase_start(char *str, t_lem *lem);
int						ft_phase_end(char *str, t_lem *lem);
int						ft_phase_links(char *str, t_lem *lem);
void					ft_affich_map(t_map *map);
void					ft_affich_paths(t_list *paths, int rec);
void					ft_affich_path(t_path *path, int rec);
void					ft_affich_list_of_list(t_list *list);
void					ft_affich_map(t_map *map);
void					ft_affich_room(t_room *room);
void					ft_affich_room_lite(t_room *room);
void					ft_affich_queue(t_list *queue);
void					ft_affich_room_list(t_list *room_list);
int						ft_process_lem_in(t_lem *lem);
int						ft_process_fill(t_room *room, t_lem *lem,
							t_list **paths, int *dist);
char					*ft_parse(t_lem *lem);
int						ft_common_checks(char *str);
int						ft_is_valid_room(char **split, t_lem *lem);
int						ft_isdigit_string(char *str);
int						ft_is_atoiable(char *str);
int						ft_share_same_infos(t_list *rooms, char **split);
int						ft_special_rooms_check(char *str, t_lem *lem);
int						ft_links_transition_check(char *str, t_lem *lem);
int						ft_add_room(char *str, t_lem *lem, int indic);
int						ft_add_link(char *str, t_lem *lem);
void					ft_init_parser(t_parser *parser);
void					ft_init_parse_arr(t_parse_func arr[5]);
void					ft_error(char *error);
void					ft_file_error(char *filename);
int						ft_is_valid_post_parse(t_lem *lem);
int						ft_add_to_list_ptr(t_list **list, void *content,
							size_t size);
int						ft_add_to_list_ptr_back(t_list **list, void *content,
							size_t size);
int						ft_copy_list_ptr_rev(t_list *list, t_list **res);
int						ft_copy_list_ptr(t_list *list, t_list **res);
int						ft_verbose(t_lem *lem, char *line, char *str);
int						ft_verbose_no_line(t_lem *lem, char *str);
void					ft_delete_rooms(t_list **rooms);
void					ft_reset_pathfinding(t_map *map);
int						ft_is_solvable(t_map *map);
t_room					*ft_get_room(t_list *rooms, char *name);
t_room					*ft_get_neighbour(t_room *room, char *room_name);
int						ft_free_turn(void *to_free, int ret);
char					*ft_free_turn_str(char **to_del, char *ret);
char					*ft_free_turn_strs(char **to_del, char **to_del2,
							char *ret);
int						ft_free_turn_split(char **split, int ret);
int						ft_free_turn_splits(char **split1, char **split2,
							int ret);
int						ft_fill_paths(t_lem *lem);
int						ft_add_path_from_rooms(t_list **paths,
							t_list *path, int length);
int						ft_update_matching_smps(t_path *path, t_path *path2);
int						ft_overlaps_path_list(t_list **paths, t_path *path);
int						ft_fill_mps(t_lem *lem);
int						ft_nb_mps_smp(t_path *path);
int						ft_fill_matching_smps(t_lem *lem);
void					ft_progress_ants(t_deploy *deploy, t_lem *lem);
int						ft_deploy_ants(t_deploy *deploy, t_lem *lem);
int						ft_deploy_ants_smp(t_path *chosen, t_deploy *deploy,
							t_lem *lem);
void					ft_init_deploy(t_deploy *deploy);
t_ant					*ft_new_ant(t_list *rooms);
int						ft_populate_platform(t_deploy_platform *p,
							t_path *chosen);
int						ft_print_solution(t_lem *lem, t_path *chosen);
t_path					*ft_chosen_path(t_lem *lem);

#endif

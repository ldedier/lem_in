/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_lem-in.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:04:38 by ldedier           #+#    #+#             */
/*   Updated: 2018/11/20 17:37:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISU_LEM_IN_H
# define FT_VISU_LEM_IN_H

# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_mixer/SDL_mixer.h>
# include "lem_in.h"
# include "libft.h"

# define GRASS_BORDER	200
# define ROOM_SIZE		150
# define ANT			0
# define ROOM			1
# define START_SPRITE	2
# define END_SPRITE		3
# define ROOM_SEL		4
# define START_SEL		5
# define END_SEL		6

# define TIME_PER_TURN	3000

typedef struct			s_alpha
{
	double				w;
	double				h;
}						t_alpha;

typedef struct			s_vant
{
	int					id;
	t_room				*room;
}						t_vant;

typedef struct			s_transition
{
	t_room				*from;
	t_room				*to;
	int					angle;
}						t_transition;

typedef struct			s_sdl
{
	SDL_Rect			screen;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*w_surface;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDL_Color			color;
	SDL_Texture			*textures[7];
	SDL_Texture			*ant_textures[4];
	TTF_Font			*font;
}						t_sdl;

typedef struct			s_stats
{
	int					top;
	int					top_fix;
	int					bottom;
	int					bottom_fix;
	int					right;
	int					right_fix;
	int					left;
	int					left_fix;
}						t_stats;

typedef struct			s_anim
{
	t_list				*transitions;
	t_list				*static_ants_rooms;
	Uint32				start;
	Uint32				previous;
	Uint32				current;
	double				progress;
	int					pause;
	int					current_animation;
}						t_anim;

typedef struct			s_grab
{
	int					x_diff;
	int					y_diff;
	t_room				*grabbed_room;
}						t_grab;

typedef struct			s_dim
{
	int					width;
	int					height;
}						t_dim;

typedef struct			s_reactive
{
	double				w_scale;
	double				h_scale;
	int					grass_border;
}						t_reactive;

typedef struct			s_env
{
	t_reactive			react;
	t_dim				dim;
	t_anim				anim;
	t_stats				stats;
	t_lem				lem;
	t_list				*vants;
	t_sdl				sdl;
	t_grab				grab;
	t_room				*selected_room;
	int					room_size;
	int					ant_number;
	int					time_per_turn;
	int					toward_end;
}						t_env;

int						ft_init_all_sdl(t_env *e);
int						ft_render(t_env *e);
void					ft_key_down(t_env *e, SDL_Keycode code);
void					ft_mouse_down(t_env *e, SDL_Event event);
void					ft_mouse_up(t_env *e, SDL_Event event);
void					ft_mouse_motion(t_env *e, SDL_Event event);
void					ft_update_corr_pos(t_env *e);
void					ft_update_room(t_map *map, int ant_num, char *room_nm);
int						ft_add_transitions(t_env *e, char *str);
void					ft_affich_transitions(t_env *e);
int						ft_add_static(t_env *e);
void					ft_gather_stats(t_env *e);
void					ft_process(t_env *e, const Uint8 *keys);
void					ft_process_end(t_env *e);
int						ft_parse_visu(t_lem *lem);
int						ft_render_visu(t_env *e, char *str);
int						ft_render_visu_end(t_env *e);
void					ft_render_rooms(t_env *e);
void					ft_render_links(t_env *e);
void					ft_render_ants(t_env *e);
void					ft_render_static_ants(t_env *e);
void					ft_reset_pos(t_env *e);
int						ft_dist(int x1, int y1, int x2, int y2);
void					ft_init_sdl_to_null(t_env *e);
void					ft_init_textures_to_null(t_env *e);
int						ft_use_texture_with_surface(t_env *e, char *title);
int						ft_render_nb_ants(t_env *e);
int						ft_render_dashboard(t_env *e);
void					ft_process_animation(t_env *e);
void					ft_fill_rect_x_y(SDL_Rect *rect, int x, int y);
void					ft_fill_rect_w_h(SDL_Rect *rect, int w, int h);
void					ft_process_current_turn(t_env *e, int *loop);
void					ft_process_end_events(t_env *e, int *loop);
t_transition            *ft_get_transition_to(t_list *transition, t_room *to);
int						ft_update_ant(t_vant *vant, t_room *to, t_env *e);
int						ft_create_ant_to(int id, char *room_name, t_env *e);
int						ft_already_in_transitions(t_list *trs, t_room *room,
							t_room *to);
t_transition			*ft_new_transition(t_room *from, t_room * to);
void					ft_apply_transition(t_env *e, t_room *from, t_room *to);
int						ft_process_ant_transition(t_vant *vant, t_room *to,
							t_env *e);
int						ft_init_textures(t_env *e);
void					ft_put_to_end(t_env *e);
void					ft_free_all(t_env *e);
#endif

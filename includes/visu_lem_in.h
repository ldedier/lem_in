/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_lem-in.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:04:38 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/20 00:23:04 by ldedier          ###   ########.fr       */
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
# define BG				1
# define ROOM			2
# define END_SPRITE		3
# define START_SPRITE	4
# define TIME_PER_TURN	3000

typedef struct			s_image
{
	void				*ptr;
	int					*data;
	int					width;
	int					height;
	int					bpp;
	int					line_size;
	int					endian;
}						t_image;

typedef struct			s_transition
{
	t_room				*from;
	t_room				*to;
	int					ant_num;
	int					angle;
}						t_transition;

typedef struct			s_sdl
{
	SDL_Rect			screen;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*surface;
	SDL_Texture			*textures[5];
	SDL_Texture			*ant_textures[4];
	TTF_Font			*fonts[3];
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
	double				progress;
	t_list				*static_ants_rooms;
	Uint32				start;
	Uint32				previous;
	Uint32				current;
	int					pause;
	int					current_animation;
}						t_anim;

typedef struct			s_keys
{
	int					down;
	int					up;
	int					right;
	int					left;
	int					can_pause;
}						t_keys;

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

typedef struct			s_env
{
	t_dim				dim;
	t_anim				anim;
	t_keys				keys;
	t_stats				stats;
	t_lem				lem;
	t_sdl				sdl;
	t_grab				grab;
	int					room_size;
	int					time_per_turn;
	int					toward_end;
}						t_env;

int						ft_init_all(t_env *e);
void					ft_render(t_env *e);
void					ft_key_down(t_env *e, SDL_Event event);
void					ft_key_up(t_env *e, SDL_Event event);
void					ft_mouse_down(t_env *e, SDL_Event event);
void					ft_mouse_up(t_env *e, SDL_Event event);
void					ft_mouse_motion(t_env *e, SDL_Event event);
void					ft_update_corr_pos(t_env *e);
void					ft_update_room(t_map *map, int ant_num, char *room_name);
void					ft_add_transitions(t_env *e, char *str);
void					ft_affich_transitions(t_env *e);
void					ft_add_static(t_env *e);
void					ft_gather_stats(t_env *e);
void					ft_process(t_env *e);
int						ft_parse_visu(t_lem *lem);
void					ft_render_visu(t_env *e, char *str);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_lem-in.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:04:38 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/17 00:00:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISU_LEM_IN_H
# define FT_VISU_LEM_IN_H

# include "lem_in.h"
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>
# include "../libft/srcs/libft.h"

# define WIN_WIDTH		1600
# define WIN_HEIGHT		1200
# define GRASS_BORDER	0
# define ROOM_SIZE		75
# define ANT			0
# define BG				1
# define MS_BY_TURN		3000

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
}						t_transition;

typedef struct			s_sdl
{
	SDL_Rect			screen;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*surface;
	SDL_Texture			*textures[5];
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
	Uint32				start;
	Uint32				current;
	char				**split;
}						t_anim;

typedef struct			s_env
{
	t_anim				anim;
	t_stats				stats;
	t_lem				lem;
	t_sdl				sdl;
	int					room_size;
	int					time_per_turn;
}						t_env;

int						ft_init_all(t_env *e);

#endif

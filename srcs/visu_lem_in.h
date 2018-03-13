/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_lem-in.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 22:04:38 by ldedier           #+#    #+#             */
/*   Updated: 2018/03/12 23:22:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VISU_LEM_IN_H
# define FT_VISU_LEM_IN_H

# include "lem_in.h"
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>
# include "../libft/srcs/libft.h"

# define WIN_WIDTH		1200
# define WIN_HEIGHT		950
# define ANT			0
# define BG				1

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

typedef struct			s_env
{
	t_stats				stats;
	t_lem				lem;
	t_sdl				sdl;
}						t_env;

int						ft_init_all(t_env *e);

#endif
